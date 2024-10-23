#include "objectdetectiondockwidget.h"
#include "./UI/ui_objectdetectiondockwidget.h"
#include <qfiledialog.h>                   //QT文件目录库，用来打开文件选择窗口

#include "mainwindows.h"
#include "QMessageBox"

ObjectDetectionDockWidget::ObjectDetectionDockWidget(MainWindow* mainWindow,QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::ObjectDetectionDockWidget)
{
    ui->setupUi(this);
    setWindowTitle("Object Detection");

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
    ui->lineEdit_img->setText(fileName);
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

