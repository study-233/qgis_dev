#include "objectdetectiondockwidget.h"
#include "./UI/ui_objectdetectiondockwidget.h"
#include <qfiledialog.h>                   //QT文件目录库，用来打开文件选择窗口

#include "mainwindows.h"
#include "QMessageBox"
#include "objectdetectionwork.h"

ObjectDetectionDockWidget::ObjectDetectionDockWidget(MainWindow* mainWindow,QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::ObjectDetectionDockWidget),
    mainWindow(mainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Object Detection");

    ui->comboBox->addItem("STD_vit_dota");
    ui->comboBox->setCurrentIndex(0);

    // 设置进度条初始值和最大值
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(100);
}

ObjectDetectionDockWidget::~ObjectDetectionDockWidget()
{
    delete ui;
}

void ObjectDetectionDockWidget::on_pushButton_selectUpl_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"));
    if (fileName.isNull()) //如果文件未选择则返回
    {
        return;
    }

    // 获取 mapCanvas1 的指针
    QgsMapCanvas *mapCanvas1 = mainWindow->getMapCanvas1();

    ui->lineEdit_img1->setText(fileName);
    QStringList temp = fileName.split('/');
    QString basename = temp.at(temp.size() - 1);//获取栅格数据名称

    //步骤2：创建QgsRasterLayer类
    QgsRasterLayer* rasterLayer = new QgsRasterLayer(fileName, basename, "gdal");
    //如果不是geotiff文件，则提示错误
    if (!rasterLayer->isValid())
    {
        QMessageBox::critical(this, "error", QString("layer is invalid: \n") + fileName);
        return;
    }

    // QgsProject::instance()->addMapLayer(rasterLayer);


    // 清除当前图层
    mapCanvas1->setLayers(QList<QgsMapLayer *>());
    // 只设置在 mapCanvas1 上
    mapCanvas1->setLayers(QList<QgsMapLayer *>() << rasterLayer);
    mapCanvas1->setExtent(rasterLayer->extent());
    mapCanvas1->zoomToFullExtent();
}


void ObjectDetectionDockWidget::on_pushButton_selectSvg_clicked()
{
    QString fileName = QFileDialog::getExistingDirectory(this, tr("Open file"));
    if (fileName.isNull()) //如果文件未选择则返回
    {
        return;
    }
    ui->lineEdit_svgPath->setText(fileName);
}


void ObjectDetectionDockWidget::on_pushButton_start_clicked()
{
    // 创建 worker 实例前，检查是否已有正在运行的任务
    if (worker) {
        QMessageBox::warning(this, "Warning", u8"已有任务正在运行，请取消后再启动新任务");
        return;
    }

    ui->progressBar->setValue(0);

    if (ui->lineEdit_img1->text().isEmpty() || ui->lineEdit_svgPath->text().isEmpty() || ui->lineEdit_svgName->text().isEmpty()) {
        QMessageBox::critical(this, "Error", QString(u8"请确保所有输入框均已填写"));
        return;
    }

    // 创建定时器
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        int currentValue = ui->progressBar->value();
        if (currentValue < 99) {
            ui->progressBar->setValue(currentValue + 1); // 每次增加10
        } else {
            timer->stop(); // 达到99后停止定时器
            delete timer; // 删除定时器
        }
    });

    // 启动定时器，每100毫秒更新一次
    timer->start(200);

    std::string imgPathStr = ui->lineEdit_img1->text().toStdString();
    std::string modelStr = ui->comboBox->currentText().toStdString();
    std::string savePathStr = ui->lineEdit_svgPath->text().toStdString();
    std::string svgNameStr = ui->lineEdit_svgName->text().toStdString();

    // 调试输出
    qDebug() << QString::fromStdString(imgPathStr) << "cpu" << QString::fromStdString(modelStr)
             << QString::fromStdString(savePathStr) << QString::fromStdString(svgNameStr);

    // 创建 PythonWorker 实例，直接传递 std::string 对象
    worker = new ObjectDetectionwork(imgPathStr, "cpu", modelStr, savePathStr, svgNameStr, this);

    // // 连接进度更新信号
    // connect(worker, &PythonWorker::progressUpdated, ui->progressBar, &QProgressBar::setValue);

    // 连接处理完成信号
    connect(worker, &ObjectDetectionwork::processingFinished, this, [this, savePathStr, svgNameStr](bool success) {
        worker->deleteLater();
        ui->progressBar->setValue(100);
        if (success) {
            QMessageBox::information(this, "Success", u8"生成成功");
            QString fileName = QString::fromStdString(savePathStr +"/"+ svgNameStr + ".png");
            mainWindow->Open_raster(fileName);
        } else {
            QMessageBox::critical(this, "Error", u8"生成失败");
        }

    });

    // 启动后台线程
    worker->start();
}


void ObjectDetectionDockWidget::on_pushButton_cancel_clicked()
{
    // 检查是否有正在运行的任务
    if (worker) {
        // 提示用户任务正在处理中，并会继续执行未完成的任务后终止
        int ret = QMessageBox::warning(this, "Cancel Task", u8"任务正在运行。任务将继续执行未完成的部分，直到处理完毕后终止。\n确认取消任务吗？",
                                       QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (ret == QMessageBox::No) {
            return; // 用户选择不取消，直接返回
        }

        // 请求中断 worker 线程
        worker->requestInterruption();

        // 等待 worker 线程结束，确保线程安全地退出
        worker->wait();  // 等待线程结束，确保线程完全退出后再进行后续操作

        // 停止进度条
        ui->progressBar->setValue(0);

        // 停止定时器
        if (timer) {
            timer->stop();
            delete timer;
            timer = nullptr;
        }

        // 清理 worker
        worker->deleteLater();
        worker = nullptr;

        // 显示任务取消的提示
        // QMessageBox::information(this, "Cancelled", u8"任务已取消");
    } else {
        QMessageBox::warning(this, "Warning", u8"没有正在运行的任务");
    }
}

