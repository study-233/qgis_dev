#include "reconstructiondockwidget.h"
#include "./UI/ui_reconstructiondockwidget.h"
#include <qfiledialog.h>                   //QT文件目录库，用来打开文件选择窗口

#include "mainwindows.h"
#include "QMessageBox"

ReconstructionDockWidget::ReconstructionDockWidget(MainWindow* mainWindow,QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::ReconstructionDockWidget)
    , mainWindow(mainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Reconstruction");
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

