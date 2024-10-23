#include "changedetectiondockwidget.h"
#include "./UI/ui_changedetectiondockwidget.h"
#include <qfiledialog.h>                   //QT文件目录库，用来打开文件选择窗口

#include "mainwindows.h"
#include "QMessageBox"

ChangeDetectionDockWidget::ChangeDetectionDockWidget(MainWindow* mainWindow,QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::ChangeDetectionDockWidget)
    , mainWindow(mainWindow)

{
    ui->setupUi(this);
    setWindowTitle("Change Detection");

}

ChangeDetectionDockWidget::~ChangeDetectionDockWidget()
{
    delete ui;
}

void ChangeDetectionDockWidget::on_pushButton_select1_clicked()
{

    // 获取 mapCanvas1 的指针
    QgsMapCanvas *mapCanvas1 = mainWindow->getMapCanvas1();  // 从 MainWindow 获取 mapCanvas1

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"));
    if (fileName.isNull()) //如果文件未选择则返回
    {
        return;
    }
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

