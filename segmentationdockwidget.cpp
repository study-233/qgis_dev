#include "segmentationdockwidget.h"
#include <qfiledialog.h>                   //QT文件目录库，用来打开文件选择窗口
#include "./UI/ui_segmentationdockwidget.h"

#include "mainwindows.h"
#include "QMessageBox"

#undef slots
#include "Python.h"
#define slots Q_SLOTS

SegmentationDockWidget::SegmentationDockWidget(MainWindow* mainWindow,QWidget *parent)
    : QDockWidget(parent),
    ui(new Ui::SegmentationDockWidget),
    mainWindow(mainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Segmentation");

    QString path = QCoreApplication::applicationDirPath() + "/aerialformer/";
    Py_SetPythonHome((wchar_t *)(reinterpret_cast<const wchar_t *>(path.utf16())));

}

SegmentationDockWidget::~SegmentationDockWidget()
{
    delete ui;
}

QString uplfileName;

void SegmentationDockWidget::on_pushButton_selectUpl_clicked()
{

    uplfileName = QFileDialog::getOpenFileName(this, tr("Open file"));
    if (uplfileName.isNull()) //如果文件未选择则返回
    {
        return;
    }
    // 获取 mapCanvas1 的指针
    QgsMapCanvas *mapCanvas1 = mainWindow->getMapCanvas1();

    ui->lineEdit_img1->setText(uplfileName);
    QStringList temp = uplfileName.split('/');
    QString basename = temp.at(temp.size() - 1);//获取栅格数据名称

    //步骤2：创建QgsRasterLayer类
    QgsRasterLayer* rasterLayer = new QgsRasterLayer(uplfileName, basename, "gdal");
    //如果不是geotiff文件，则提示错误
    if (!rasterLayer->isValid())
    {
        QMessageBox::critical(this, "error", QString("layer is invalid: \n") + uplfileName);
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


void SegmentationDockWidget::on_pushButton_selectSvg_clicked()
{
    QString fileName = QFileDialog::getExistingDirectory(this, tr("Open file"));
    if (fileName.isNull()) //如果文件未选择则返回
    {
        return;
    }
    ui->lineEdit_svgPath->setText(fileName);
}

void SegmentationDockWidget::on_pushButton_start_clicked()
{

    //初始化python模块
    Py_Initialize();
    if(!Py_IsInitialized())
    {
        qDebug() <<"Initialize fail";
    }
    // 导入sys模块设置模块地址，以及python脚本路径
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./release/py_scripts/AerialFormer')");

    // 加载 python 脚本
    PyObject *pModule = PyImport_ImportModule("sem_seg");  // 脚本名称，不带.py

    if (!pModule)
    {
        qDebug() << "Failed to load Python module 'sem_seg'";
        Py_Finalize();
        return;
    }

    // 获取 sem_seg 函数
    PyObject *pFunc = PyObject_GetAttrString(pModule, "sem_seg");
    if (!pFunc || !PyCallable_Check(pFunc))
    {
        qDebug() << "Failed to get Python function 'sem_seg'";
        Py_DECREF(pModule);  // 释放模块
        Py_Finalize();
        return;
    }
    // 设置传入的参数（设备）
    const char *img_path = "C:\\Users\\Administrator\\Desktop\\qgis_testimg\\Potsdam_sample\\images\\7_13_5488_0_6000_512.png";  // 传递图片路径
    const char *out_path = "C:\\Users\\Administrator\\Desktop";
    const char *device = "cpu";               // 可选的设备参数

    // 构建参数对象
    PyObject *pArgs = PyTuple_New(3);  // 2 个参数
    PyTuple_SetItem(pArgs, 0, PyUnicode_FromString(img_path));  // 设置图片路径参数
    PyTuple_SetItem(pArgs, 1, PyUnicode_FromString(out_path));  // 设置存储路径参数
    PyTuple_SetItem(pArgs, 2, PyUnicode_FromString(device));    // 设置设备参数

    // 调用 Python 函数
    PyObject *pResult = PyObject_CallObject(pFunc, pArgs);

    // 检查调用是否成功
    if (pResult)
    {
        qDebug() << "Python function 'sem_seg' executed successfully.";

        // 处理返回值（假设返回的是二维数组）
        // 此处可以根据返回结果的类型做进一步处理
    }
    else
    {
        qDebug() << "Python function 'sem_seg' execution failed.";
        PyErr_Print();  // 打印 Python 错误信息
    }

    // 释放对象
    Py_XDECREF(pResult);
    Py_DECREF(pArgs);
    Py_DECREF(pFunc);
    Py_DECREF(pModule);

    // 关闭 Python 环境
    Py_Finalize();

}

