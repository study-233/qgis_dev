#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMath>
#include <QStackedWidget>

//工具类
#include "segmentationdockwidget.h"
#include "changedetectiondockwidget.h"
#include "objectdetectiondockwidget.h"
#include "reconstructiondockwidget.h"

//库
#include <qmenu.h>                  //QT菜单类
#include <qaction.h>                //QT行为类

#include "qgsrasterlayer.h"         //QGIS栅格图层
#include "qgsvectorlayer.h"         //QGIS矢量图层
#include "qgsmaplayer.h"            //QGIS图层
#include "qgsmapcanvas.h"           //QGIS画布

#include "qgslayertreeview.h"              //QGIS图层管理器
#include "qgslayertreemapcanvasbridge.h"   //连接画布和图层管理器

#include "QOpenGLFunctions"
#include <Qgs3DMapCanvas.h>

class ObjectDetectionDockWidget;

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE


class MainWindow : public QMainWindow ,protected QOpenGLFunctions
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static MainWindow* instance() { return my; }
    QgsMapCanvas* getMapCanvas1() const { return mapCanvas1; }
    QgsMapCanvas* getMapCanvas2() const { return mapCanvas2; }
    QTabWidget* getTabWidget() const {return tabWidget;}

private slots:
    void on_actionOpen_raster_triggered();

    void on_actionOpen_vector_triggered();

    void on_actionRemove_file_triggered();

    void slot_autoSelectAddedLayer(QList<QgsMapLayer*> layers);

    void showAllLayers();

    void hideAllLayers();

    void showSelectedLayers();

    void hideSelectedLayers();

    void removeLayer();

    void slot_save_layout();

    void on_actionImport_mask_triggered();

    void slot_restart_layout();

    // void on_action3dtest_triggered();

private:
    Ui::MainWindow *ui;
    static MainWindow *my;

    SegmentationDockWidget *mSegmentation = nullptr;
    ChangeDetectionDockWidget *mChangeDetection = nullptr;
    ObjectDetectionDockWidget *mObjectDetection = nullptr;
    ReconstructionDockWidget *mReconstruction = nullptr;

    QDockWidget* m_layerTreeDock = nullptr;

    QAction *save_layout,*restart_layout;
    QSettings *setting; //保存布局用的配置文件类,也可以用别的方式保存

    //地图画布
    QgsMapCanvas *mapCanvas1;  // 预览画布
    QgsMapCanvas *mapCanvas2;
    QgsMapCanvas *mapCanvas;
    Qgs3DMapCanvas *canvas ;
    QTabWidget *tabWidget;  // 或者 QTabWidget *tabWidget

    QList<QgsMapLayer*> layers;              //存储加载的图层

    //3d
    QgsWindow3DEngine *engine;
    Qgs3DMapScene *scene;
    QWidget *widget;

    //图层管理器
    QgsLayerTreeView* layerTreeView;
    QgsLayerTreeMapCanvasBridge* layerTreeCanvasBridge;

public:
    void PythonInit();          //初始化python
    void initLayerTreeView();               //初始化图层管理器函数
    void addDockWidget(Qt::DockWidgetArea area, QDockWidget* dockwidget); //添加可悬浮窗口初始位置
    void legendLayerZoomNative();
    void Import_mask(QString fileName);
    void Open_raster(QString fileName);
};
#endif // MAINWINDOW_H
