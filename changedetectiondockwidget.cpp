#include "changedetectiondockwidget.h"
#include "./UI/ui_changedetectiondockwidget.h"
#include <qfiledialog.h>                   //QT文件目录库，用来打开文件选择窗口

#include "mainwindows.h"
#include "QMessageBox"
#include "changedetectionwork.h"

ChangeDetectionDockWidget::ChangeDetectionDockWidget(MainWindow* mainWindow,QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::ChangeDetectionDockWidget)
    , mainWindow(mainWindow)

{
    ui->setupUi(this);
    setWindowTitle("Change Detection");

    ui->comboBox->addItem("A2Net");
    ui->comboBox->setCurrentIndex(0);

    // 设置进度条初始值和最大值
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(100);
}

ChangeDetectionDockWidget::~ChangeDetectionDockWidget()
{
    delete ui;
}

void ChangeDetectionDockWidget::on_pushButton_select1_clicked()
{


    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"));
    if (fileName.isNull()) //如果文件未选择则返回
    {
        return;
    }
    ui->lineEdit_img1->setText(fileName);
    QStringList temp = fileName.split('/');
    QString basename = temp.at(temp.size() - 1);//获取栅格数据名称

    // 获取 mapCanvas1 的指针
    QgsMapCanvas *mapCanvas1 = mainWindow->getMapCanvas1();  // 从 MainWindow 获取 mapCanvas1

    //步骤2：创建QgsRasterLayer类
    QgsRasterLayer* rasterLayer = new QgsRasterLayer(fileName, basename, "gdal");
    //如果不是geotiff文件，则提示错误
    if (!rasterLayer->isValid())
    {
        QMessageBox::critical(this, "error", QString("layer is invalid: \n") + fileName);
        return;
    }

    //QgsProject::instance()->addMapLayer(rasterLayer);

    // 确保只对 mapCanvas1 设置图层
    mapCanvas1->setLayers(QList<QgsMapLayer *>() << rasterLayer);
    mapCanvas1->setExtent(rasterLayer->extent());
    mapCanvas1->zoomToFullExtent();

}


void ChangeDetectionDockWidget::on_pushButton_select2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"));
    if (fileName.isNull()) //如果文件未选择则返回
    {
        return;
    }
    // 获取 mapCanvas2 的指针
    QgsMapCanvas *mapCanvas2 = mainWindow->getMapCanvas2();  // 从 MainWindow 获取 mapCanvas2

    ui->lineEdit_img2->setText(fileName);

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

    //QgsProject::instance()->addMapLayer(rasterLayer);

    // 确保只对 mapCanvas1 设置图层
    mapCanvas2->setLayers(QList<QgsMapLayer *>() << rasterLayer);
    mapCanvas2->setExtent(rasterLayer->extent());
    mapCanvas2->zoomToFullExtent();

}


void ChangeDetectionDockWidget::on_pushButton_selectSvg_clicked()
{
    QString fileName = QFileDialog::getExistingDirectory(this, tr("Open file"));
    if (fileName.isNull()) //如果文件未选择则返回
    {
        return;
    }
    ui->lineEdit_svgPath->setText(fileName);
}


void ChangeDetectionDockWidget::on_pushButton_start_clicked()
{
    ui->progressBar->setValue(0);

    if (ui->lineEdit_img1->text().isEmpty() || ui->lineEdit_img2->text().isEmpty() || ui->lineEdit_svgPath->text().isEmpty() || ui->lineEdit_svgName->text().isEmpty()) {
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

    std::string imgPathStr1 = ui->lineEdit_img1->text().toStdString();
    std::string imgPathStr2 = ui->lineEdit_img2->text().toStdString();
    std::string modelStr = ui->comboBox->currentText().toStdString();
    std::string savePathStr = ui->lineEdit_svgPath->text().toStdString();
    std::string svgNameStr = ui->lineEdit_svgName->text().toStdString()+".png";

    // 调试输出
    qDebug() << QString::fromStdString(imgPathStr1) << QString::fromStdString(imgPathStr2) << "gpu" << QString::fromStdString(modelStr)
             << QString::fromStdString(savePathStr) << QString::fromStdString(svgNameStr);

    // 创建 PythonWorker 实例，直接传递 std::string 对象
    ChangeDetectionwork *worker = new ChangeDetectionwork(imgPathStr1, imgPathStr2, "gpu", modelStr, savePathStr, svgNameStr, this);

    // // 连接进度更新信号
    // connect(worker, &ChangeDetectionwork::progressUpdated, ui->progressBar, &QProgressBar::setValue);

    // 连接处理完成信号
    connect(worker, &ChangeDetectionwork::processingFinished, this, [this, worker](bool success) {
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

