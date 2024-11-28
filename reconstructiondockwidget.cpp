#include "reconstructiondockwidget.h"
#include "./UI/ui_reconstructiondockwidget.h"
#include <qfiledialog.h>                   //QT文件目录库，用来打开文件选择窗口

#include "mainwindows.h"
#include "QMessageBox"
#include "reconstructionwork.h"

ReconstructionDockWidget::ReconstructionDockWidget(MainWindow* mainWindow,QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::ReconstructionDockWidget)
    , mainWindow(mainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Reconstruction");

    ui->comboBox->addItem("sr");
    ui->comboBox->setCurrentIndex(0);

    // 设置进度条初始值和最大值
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(100);
}

ReconstructionDockWidget::~ReconstructionDockWidget()
{
    delete ui;
}

void ReconstructionDockWidget::on_pushButton_selectUpl_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"));
    if (fileName.isNull()) //如果文件未选择则返回
    {
        return;
    }
    QStringList temp = fileName.split('/');
    QString basename = temp.at(temp.size() - 1);//获取栅格数据名称
    ui->lineEdit_img->setText(fileName);

    // 获取 mapCanvas1 的指针
    QgsMapCanvas *mapCanvas1 = mainWindow->getMapCanvas1();


    //创建QgsRasterLayer类
    QgsRasterLayer* rasterLayer = new QgsRasterLayer(fileName, basename, "gdal");
    //如果不是geotiff文件，则提示错误
    if (!rasterLayer->isValid())
    {
        QMessageBox::critical(this, "error", QString("layer is invalid: \n") + fileName);
        return;
    }

    QgsProject::instance()->addMapLayer(rasterLayer);
    // 清除当前图层
    mapCanvas1->setLayers(QList<QgsMapLayer *>());
    // 只设置在 mapCanvas1 上
    mapCanvas1->setLayers(QList<QgsMapLayer *>() << rasterLayer);
    mapCanvas1->setExtent(rasterLayer->extent());
    mapCanvas1->zoomToFullExtent();
}


void ReconstructionDockWidget::on_pushButton_selectSvg_clicked()
{
    QString fileName = QFileDialog::getExistingDirectory(this, tr("Open file"));
    if (fileName.isNull()) //如果文件未选择则返回
    {
        return;
    }
    ui->lineEdit_svgPath->setText(fileName);
}


void ReconstructionDockWidget::on_pushButton_start_clicked()
{
    ui->progressBar->setValue(0);

    if (ui->lineEdit_img->text().isEmpty() || ui->lineEdit_svgPath->text().isEmpty() || ui->lineEdit_svgName->text().isEmpty()) {
        QMessageBox::critical(this, "Error", QString(u8"请确保所有输入框均已填写"));
        return;
    }

    // 创建定时器
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this, timer]() {
        int currentValue = ui->progressBar->value();
        if (currentValue < 99) {
            ui->progressBar->setValue(currentValue + 1); // 每次增加10
        } else {
            timer->stop(); // 达到99后停止定时器
            delete timer; // 删除定时器
        }
    });

    // 启动定时器，每100毫秒更新一次
    timer->start(70);

    std::string imgPathStr = ui->lineEdit_img->text().toStdString();
    std::string modelStr = ui->comboBox->currentText().toStdString();
    std::string savePathStr = ui->lineEdit_svgPath->text().toStdString();
    std::string svgNameStr = ui->lineEdit_svgName->text().toStdString()+".png";

    // 调试输出
    qDebug() << QString::fromStdString(imgPathStr) << "cpu" << QString::fromStdString(modelStr)
             << QString::fromStdString(savePathStr) << QString::fromStdString(svgNameStr);

    // 创建 PythonWorker 实例，直接传递 std::string 对象
    Reconstructionwork *worker = new Reconstructionwork(imgPathStr, "cuda:0", modelStr, savePathStr, svgNameStr, this);

    // // 连接进度更新信号
    // connect(worker, &Reconstructionwork::progressUpdated, ui->progressBar, &QProgressBar::setValue);

    // 连接处理完成信号
    connect(worker, &Reconstructionwork::processingFinished, this, [this, worker](bool success) {
        worker->deleteLater();
        ui->progressBar->setValue(100);
        if (success) {
            QMessageBox::information(this, "Success", u8"生成成功");
        } else {
            QMessageBox::critical(this, "Error", u8"生成失败");
        }

    });

    // 启动后台线程
    worker->start();
}

