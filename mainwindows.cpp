#include "mainwindows.h"
#include "./UI/ui_mainwindows.h"
#include <QDebug>
#include <QToolBar>

//test
#include "qgsrastershader.h"
#include <qgssinglebandpseudocolorrenderer.h>

//自己引入的库
#include "QTextCodec"
#include <qmenubar.h>                      //QT菜单栏库，用来存放菜单
#include <qfiledialog.h>                   //QT文件目录库，用来打开文件选择窗口
#include "qmessagebox.h"                   //QT信息盒子，用来显示操作提示

#include "qgslayertreemodel.h"            //使用给定层树构建新的树模型,一般与QgsLayerTreeView 一起使用
#include "qgridlayout.h"                  //栅格布局管理器

#include "qtoolbutton.h"                  //工具按钮,和普通工具相比可以带图标
#include "qdockwidget.h"                  //可悬浮窗口
#include "qgis_devlayertreeviewmenuprovider.h" //图层管理器右键菜单类
#include "qgslayertreeregistrybridge.h"        //创建与层树根同步给定项目的实例,收听地图层注册表中的更新，并在层树中进行更改。

#include <qgscolorrampshader.h>
//3d
#include <Qgs3DMapCanvas.h>
#include <Qgs3DMapSettings.h>
#include <Qgs3DMapScene.h>
#include <qgs3dmapcontroller.h>
#include "qgswindow3dengine.h"

MainWindow *MainWindow::my = nullptr;

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    my = this;

    setWindowTitle(u8"高分遥感图像分析");

    this->resize(1500, 600);        //设置窗口大小

    tabWidget = new QTabWidget();

    // 初始化第一个预览
    mapCanvas1 = new QgsMapCanvas();
    mapCanvas1->setCachingEnabled(true);
    mapCanvas1->setCanvasColor(QColor(255, 255, 255));  // 设置地图画布为白色
    mapCanvas1->setVisible(true);
    mapCanvas1->enableAntiAliasing(true);

    // 初始化第二个预览
    mapCanvas2 = new QgsMapCanvas();
    mapCanvas2->setCachingEnabled(true);
    mapCanvas2->setCanvasColor(QColor(255, 255, 255));  // 设置地图画布为白色
    mapCanvas2->setVisible(true);
    mapCanvas2->enableAntiAliasing(true);

    //初始化地图画布
    mapCanvas = new QgsMapCanvas();
    mapCanvas->setCachingEnabled(true);
    mapCanvas->setCanvasColor(QColor(255, 255, 255));   //设置地图画布为白色
    mapCanvas->setVisible(true);
    mapCanvas->enableAntiAliasing(true);

    // 将地图画布添加到分页控件中
    tabWidget->addTab(mapCanvas1, u8"预览1");
    tabWidget->addTab(mapCanvas2, u8"预览2");
    tabWidget->addTab(mapCanvas, u8"输出");

    auto gridLayout = new QGridLayout;
    gridLayout->addWidget(tabWidget);
    centralWidget()->setLayout(gridLayout);

    //初始化图层管理器
    layerTreeView = new QgsLayerTreeView(this);
    initLayerTreeView();

    addDockWidget(Qt::RightDockWidgetArea, m_layerTreeDock);        //初始位置
    ui->menuTool->addAction(m_layerTreeDock->toggleViewAction());

    mSegmentation = new SegmentationDockWidget(this);
    this->addDockWidget(Qt::LeftDockWidgetArea,mSegmentation);
    ui->menuTool->addAction(mSegmentation->toggleViewAction());

    mChangeDetection = new ChangeDetectionDockWidget(this,this);
    tabifyDockWidget(mSegmentation,mChangeDetection);
    ui->menuTool->addAction(mChangeDetection->toggleViewAction());

    mObjectDetection = new ObjectDetectionDockWidget(this,this);
    tabifyDockWidget(mSegmentation,mObjectDetection);
    ui->menuTool->addAction(mObjectDetection->toggleViewAction());

    mReconstruction = new ReconstructionDockWidget(this);
    tabifyDockWidget(mSegmentation,mReconstruction);
    ui->menuTool->addAction(mReconstruction->toggleViewAction());

    mSegmentation->raise();
    QMenu *menu = ui->menuSetting->addMenu(u8"布局设置");

    save_layout = new QAction(u8"保存布局");
    connect(save_layout,&QAction::triggered,this,&MainWindow::slot_save_layout);
    menu->addAction(save_layout);

    restart_layout = new QAction(u8"恢复布局");
    connect(restart_layout,&QAction::triggered,this,&MainWindow::slot_restart_layout);
    menu->addAction(restart_layout);


    //exe执行程序旁边生成一个配置文件,用来寸界面布局QDockWidget类成员的信息,文件名随便取,格式随便写
    setting = new QSettings(QCoreApplication::applicationDirPath() + "/layout_config.txt",QSettings::IniFormat);
    setting->setIniCodec(QTextCodec::codecForName("utf-8"));//文件字节编码设置成utf-8


}


void MainWindow::on_actionOpen_raster_triggered()
{
    //步骤1：打开文件选择对话框
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open raster file"), "", "remote sensing image(*.jpg *.jpeg *.png *.bmp *.img);;image(*.tif *.tiff)");
    if (fileName.isNull()) //如果文件未选择则返回
    {
        return;
    }
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


    //步骤3：添加栅格数据
    QgsProject::instance()->addMapLayer(rasterLayer); //注册
    mapCanvas->setExtent(rasterLayer->extent());     //将画布范围设置为栅格图层范围
    layers.append(rasterLayer);                      //将栅格图层追加到链表中
    mapCanvas->setLayers(layers);                    //将图层画到画布上
    mapCanvas->setVisible(true);
    mapCanvas->freeze(false);
    mapCanvas->refresh();                           //更新画布

}


void MainWindow::on_actionOpen_vector_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open shape file"), "", "*.shp");
    if (fileName.isNull()) //如果文件未选择则返回
    {
        return;
    }

    QStringList temp = fileName.split('/');
    QString basename = temp.at(temp.size() - 1);
    QgsVectorLayer* vecLayer = new QgsVectorLayer(fileName, basename, "ogr");

    if (!vecLayer->isValid())
    {
        QMessageBox::critical(this, "error", QString("layer is invalid: \n") + fileName);
        return;
    }

    //QGIS 3注册方式
    QgsProject::instance()->addMapLayer(vecLayer);

    mapCanvas->setExtent(vecLayer->extent());
    layers.append(vecLayer);
    mapCanvas->setLayers(layers);
    mapCanvas->setVisible(true);
    mapCanvas->freeze(false);
    mapCanvas->refresh();

}



//TEST
void MainWindow::on_actiontest_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open raster file"), "", "remote sensing image(*.jpg *.jpeg *.png *.bmp);;image(*.tif *.tiff)");
    if (fileName.isNull()) //如果文件未选择则返回
    {
        return;
    }
    QStringList temp = fileName.split('/');
    QString basename = temp.at(temp.size() - 1);//获取栅格数据名称

    // 1. 加载mask图层
    QgsRasterLayer* maskLayer = new QgsRasterLayer(fileName, basename, "gdal");
    if (!maskLayer->isValid())
    {
        qDebug() << "Mask layer failed to load!";
        return;
    }

    // 2. 创建颜色映射
    QgsRasterShader* rasterShader = new QgsRasterShader();
    QgsColorRampShader* colorRampShader = new QgsColorRampShader();

    // 使用Qgis::ShaderInterpolationMethod 来设置颜色映射类型
    colorRampShader->setColorRampType(Qgis::ShaderInterpolationMethod::Linear);

    // 使用QList来存储ColorRampItem
    QList<QgsColorRampShader::ColorRampItem> colorRampItems;

    // 定义每个类别的颜色
    // 0 - impervious_surface
    colorRampItems.append(QgsColorRampShader::ColorRampItem(0, QColor(255, 255, 255), "Impervious Surface"));

    // 1 - building
    colorRampItems.append(QgsColorRampShader::ColorRampItem(1, QColor(255, 0, 0), "Building"));

    // 2 - meadow
    colorRampItems.append(QgsColorRampShader::ColorRampItem(2, QColor(0, 255, 0), "Meadow"));

    // 3 - tree
    colorRampItems.append(QgsColorRampShader::ColorRampItem(3, QColor(0, 128, 0), "Tree"));

    // 4 - car
    colorRampItems.append(QgsColorRampShader::ColorRampItem(4, QColor(0, 0, 255), "Car"));

    // 255 - 背景类
    colorRampItems.append(QgsColorRampShader::ColorRampItem(255, QColor(0, 0, 0, 0), "Background"));

    // 将ColorRampItem列表应用到colorRampShader
    colorRampShader->setColorRampItemList(colorRampItems);
    rasterShader->setRasterShaderFunction(colorRampShader);
    int band = 1; // 假设我们使用的是第一个波段

    // 3. 创建渲染器并应用颜色映射
    QgsRasterRenderer* renderer = new QgsSingleBandPseudoColorRenderer(maskLayer->dataProvider(), band, rasterShader);

    maskLayer->setRenderer(renderer);
    maskLayer->setOpacity(0.3);

    // 4. 将mask图层添加到当前项目并显示在canvas上
    QgsProject::instance()->addMapLayer(maskLayer); //注册
    mapCanvas->setExtent(maskLayer->extent());     //将画布范围设置为栅格图层范围
    layers.append(maskLayer);                      //将栅格图层追加到链表中
    mapCanvas->setLayers(layers);                    //将图层画到画布上
    mapCanvas->setVisible(true);
    mapCanvas->freeze(false);
    mapCanvas->refresh();                           //更新画布

}



void MainWindow::on_actionRemove_file_triggered()
{
    layers.clear();                                 //从链表中清除所有图层
    mapCanvas->setLayers(layers);                   //将图层画到画布上
    mapCanvas->setVisible(true);
    mapCanvas->freeze(false);
    mapCanvas->refresh();                           //更新画布
    // 清空图层管理器中的内容

    QgsProject* project = QgsProject::instance();
    if (project) {
        QgsLayerTree* root = project->layerTreeRoot();
        if (root) {
            root->clear();  // 清除所有图层
        }
    }
}

//初始化图层管理器
void MainWindow::initLayerTreeView()
{
    QgsLayerTreeModel* model = new QgsLayerTreeModel(QgsProject::instance()->layerTreeRoot(), this);
    model->setFlag(QgsLayerTreeModel::AllowNodeRename);
    model->setFlag(QgsLayerTreeModel::AllowNodeReorder);
    model->setFlag(QgsLayerTreeModel::AllowNodeChangeVisibility);
    model->setFlag(QgsLayerTreeModel::ShowLegendAsTree);
    model->setAutoCollapseLegendNodes(10);
    layerTreeView->setModel(model);

    //右键菜单
    layerTreeView->setMenuProvider(new qgis_devLayerTreeViewMenuProvider(layerTreeView, mapCanvas));
    //connect(QgsProject::instance()->layerTreeRegistryBridge(), SIGNAL(addedLayersToLayerTree(const QList<QgsMapLayer*>)), this,
    //    SLOT(slot_autoSelectAddedLayer(const QList<QgsMapLayer*>)));
    connect(QgsProject::instance()->layerTreeRegistryBridge(), &QgsLayerTreeRegistryBridge::addedLayersToLayerTree, this,
            &MainWindow::slot_autoSelectAddedLayer);

    // 设置这个路径是为了获取图标文件
    QString iconDir = "E:\\QtDocuments\\My_Qgis\\image\\"; //注意包含中文路径图标会不显示，这里的图标可以去原QGIS软件中去找

    // QgsLayerTreeViewDefaultActions包含了默认实现的函数如添加Group
    QAction *actionAddGroup = new QAction( tr( "Add Group" ), this );
    actionAddGroup->setIcon( QIcon(iconDir + "mActionAddGroup.png"));
    actionAddGroup->setToolTip( tr( "Add Group" ) );
    connect( actionAddGroup, &QAction::triggered, layerTreeView->defaultActions(), &QgsLayerTreeViewDefaultActions::addGroup );

    QAction *actionShowAllLayers = new QAction( tr( "Show All Layers" ), this );
    actionShowAllLayers->setIcon( QIcon(iconDir + "mActionShowAllLayers.png"));
    actionShowAllLayers->setToolTip( tr( "Show All Layers" ) );
    connect(actionShowAllLayers,&QAction::triggered,this,&MainWindow::showAllLayers);

    QAction *actionHideAllLayers = new QAction( tr( "Hide All Layers" ), this );
    actionHideAllLayers->setIcon( QIcon(iconDir + "mActionHideAllLayers.png"));
    actionHideAllLayers->setToolTip( tr( "Hide All Layers" ) );
    connect(actionHideAllLayers,&QAction::triggered,this,&MainWindow::hideAllLayers);

    QAction *actionShowSelectedLayers = new QAction( tr( "Show Selected Layers" ), this );
    actionShowSelectedLayers->setIcon( QIcon(iconDir + "mActionShowSelectedLayers.png"));
    actionShowSelectedLayers->setToolTip( tr( "Show Selected Layers" ) );
    connect(actionShowSelectedLayers,&QAction::triggered,this,&MainWindow::showSelectedLayers);

    QAction *actionHideSelectedLayers = new QAction( tr( "Hide Selected Layers" ), this );
    actionHideSelectedLayers->setIcon( QIcon(iconDir + "mActionHideSelectedLayers.png"));
    actionHideSelectedLayers->setToolTip( tr( "Hide Selected Layers" ) );
    connect(actionHideSelectedLayers,&QAction::triggered,this,&MainWindow::hideSelectedLayers);

    // expand / collapse tool buttons
    QAction *actionExpandAll = new QAction( tr( "Expand All" ), this );
    actionExpandAll->setIcon( QIcon(iconDir + "mActionExpandTree.png") );
    actionExpandAll->setToolTip( tr( "Expand All" ) );
    connect( actionExpandAll, &QAction::triggered, layerTreeView, &QgsLayerTreeView::expandAllNodes );
    QAction *actionCollapseAll = new QAction( tr( "Collapse All" ), this );
    actionCollapseAll->setIcon( QIcon(iconDir + "mActionCollapseTree.png") );
    actionCollapseAll->setToolTip( tr( "Collapse All" ) );
    connect( actionCollapseAll, &QAction::triggered, layerTreeView, &QgsLayerTreeView::collapseAllNodes );

    QAction *actionRemoveLayer = new QAction( tr( "Remove Layer" ), this );
    actionRemoveLayer->setIcon( QIcon(iconDir + "mActionRemoveLayer.png") );
    actionRemoveLayer->setToolTip(tr( "Remvoe Layer" ));
    connect(actionRemoveLayer,&QAction::triggered,this,&MainWindow::removeLayer);

    //在DockWidget上部添加一个工具栏
    QToolBar *toolbar = new QToolBar();
    //    toolbar->setIconSize( iconSize( true ) );
    //    toolbar->addAction( mActionStyleDock );
    toolbar->addAction( actionAddGroup );
    toolbar->addAction( actionShowAllLayers );
    toolbar->addAction( actionHideAllLayers );
    toolbar->addAction( actionShowSelectedLayers );
    toolbar->addAction( actionHideSelectedLayers );
    toolbar->addAction( actionExpandAll );
    toolbar->addAction( actionCollapseAll );
    toolbar->addAction( actionRemoveLayer );

    //将工具栏和Layer Tree View添加到界面
    QVBoxLayout *vboxLayout = new QVBoxLayout;
    vboxLayout->setContentsMargins(0, 0, 0, 0);
    vboxLayout->setSpacing(0);
    vboxLayout->addWidget(toolbar);
    vboxLayout->addWidget(layerTreeView);

    // 装进dock widget中
    m_layerTreeDock = new QDockWidget(tr("Layer Tree"), this);
    m_layerTreeDock->setObjectName("Layers");
    m_layerTreeDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QWidget* w = new QWidget();
    w->setLayout(vboxLayout);
    m_layerTreeDock->setWidget(w);

    // 连接地图画布和图层管理器
    layerTreeCanvasBridge = new QgsLayerTreeMapCanvasBridge(QgsProject::instance()->layerTreeRoot(), mapCanvas, this);
    connect(QgsProject::instance(), SIGNAL(writeProject(QDomDocument&)),
            layerTreeCanvasBridge, SLOT(writeProject(QDomDocument&)));
    connect(QgsProject::instance(), SIGNAL(readProject(QDomDocument)),
            layerTreeCanvasBridge, SLOT(readProject(QDomDocument)));
}

//
void MainWindow::slot_autoSelectAddedLayer(const QList<QgsMapLayer*> layers)
{
    if (!layers.isEmpty())
    {
        QgsLayerTreeLayer* nodeLayer = QgsProject::instance()->layerTreeRoot()->findLayer(layers[0]->id());

        if (!nodeLayer)
            return;

        QModelIndex index = layerTreeView->layerTreeModel()->node2index(nodeLayer);
        layerTreeView->setCurrentIndex(index);
    }
}

void MainWindow::addDockWidget(Qt::DockWidgetArea area, QDockWidget* dockwidget)
{
    QMainWindow::addDockWidget(area, dockwidget);
    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    dockwidget->show();
    mapCanvas->refresh();
}


void MainWindow::legendLayerZoomNative()
{
    if ( !layerTreeView )
        return;

    //find current Layer
    QgsMapLayer *currentLayer = layerTreeView->currentLayer();
    if ( !currentLayer )
        return;

    if ( QgsRasterLayer *layer = qobject_cast<QgsRasterLayer *>( currentLayer ) )
    {
        QgsDebugMsgLevel( "Raster units per pixel  : " + QString::number( layer->rasterUnitsPerPixelX() ), 2 );
        QgsDebugMsgLevel( "MapUnitsPerPixel before : " + QString::number( mapCanvas->mapUnitsPerPixel() ), 2 );

        QList< double >nativeResolutions;
        if ( layer->dataProvider() )
        {
            nativeResolutions = layer->dataProvider()->nativeResolutions();
        }

        // get length of central canvas pixel width in source raster crs
        QgsRectangle e = mapCanvas->extent();
        QSize s = mapCanvas->mapSettings().outputSize();
        QgsPointXY p1( e.center().x(), e.center().y() );
        QgsPointXY p2( e.center().x() + e.width() / s.width(), e.center().y() + e.height() / s.height() );
        QgsCoordinateTransform ct( mapCanvas->mapSettings().destinationCrs(), layer->crs(), QgsProject::instance() );
        p1 = ct.transform( p1 );
        p2 = ct.transform( p2 );
        const double diagonalSize = std::sqrt( p1.sqrDist( p2 ) ); // width (actually the diagonal) of reprojected pixel
        if ( !nativeResolutions.empty() )
        {
            // find closest native resolution
            QList< double > diagonalNativeResolutions;
            diagonalNativeResolutions.reserve( nativeResolutions.size() );
            for ( double d : std::as_const( nativeResolutions ) )
                diagonalNativeResolutions << std::sqrt( 2 * d * d );

            int i;
            for ( i = 0; i < diagonalNativeResolutions.size() && diagonalNativeResolutions.at( i ) < diagonalSize; i++ )
            {
                QgsDebugMsgLevel( QStringLiteral( "test resolution %1: %2" ).arg( i ).arg( diagonalNativeResolutions.at( i ) ), 2 );
            }
            if ( i == nativeResolutions.size() ||
                ( i > 0 && ( ( diagonalNativeResolutions.at( i ) - diagonalSize ) > ( diagonalSize - diagonalNativeResolutions.at( i - 1 ) ) ) ) )
            {
                QgsDebugMsgLevel( QStringLiteral( "previous resolution" ), 2 );
                i--;
            }

            mapCanvas->zoomByFactor( nativeResolutions.at( i ) / mapCanvas->mapUnitsPerPixel() );
        }
        else
        {
            mapCanvas->zoomByFactor( std::sqrt( layer->rasterUnitsPerPixelX() * layer->rasterUnitsPerPixelX() + layer->rasterUnitsPerPixelY() * layer->rasterUnitsPerPixelY() ) / diagonalSize );
        }

        mapCanvas->refresh();
        QgsDebugMsgLevel( "MapUnitsPerPixel after  : " + QString::number( mapCanvas->mapUnitsPerPixel() ), 2 );
    }
}



void MainWindow::showAllLayers()
{
    QgsDebugMsgLevel( QStringLiteral( "Showing all layers!" ), 3 );
    layerTreeView->layerTreeModel()->rootGroup()->setItemVisibilityCheckedRecursive( true );
}

void MainWindow::hideAllLayers()
{
    QgsDebugMsgLevel( QStringLiteral( "hiding all layers!" ), 3 );

    const auto constChildren = layerTreeView->layerTreeModel()->rootGroup()->children();
    for ( QgsLayerTreeNode *node : constChildren )
    {
        node->setItemVisibilityCheckedRecursive( false );
    }
}

void MainWindow::showSelectedLayers()
{
    QgsDebugMsgLevel( QStringLiteral( "show selected layers!" ), 3 );

    const auto constSelectedNodes = layerTreeView->selectedNodes();
    for ( QgsLayerTreeNode *node : constSelectedNodes )
    {
        QgsLayerTreeNode *nodeIter = node;
        while ( nodeIter )
        {
            nodeIter->setItemVisibilityChecked( true );
            nodeIter = nodeIter->parent();
        }
    }
}

void MainWindow::hideSelectedLayers()
{
    QgsDebugMsgLevel( QStringLiteral( "hiding selected layers!" ), 3 );

    const auto constSelectedNodes = layerTreeView->selectedNodes();
    for ( QgsLayerTreeNode *node : constSelectedNodes )
    {
        node->setItemVisibilityChecked( false );
    }
}

void MainWindow::removeLayer()
{
    if(!layerTreeView)
        return;
    //    const QList<QgsMapLayer *> selectedLayers = mLayerTreeView->selectedLayersRecursive();

    if ( QMessageBox::warning(my, tr( "Remove layers and groups" ), tr("Are you sure?"), QMessageBox::Ok | QMessageBox::Cancel ) == QMessageBox::Cancel )
    {
        return;
    }

    const QList<QgsLayerTreeNode *> selectedNodes = layerTreeView->selectedNodes( true );
    for ( QgsLayerTreeNode *node : selectedNodes )
    {
        if ( QgsLayerTreeGroup *group = qobject_cast< QgsLayerTreeGroup * >( node ) )
        {
            if ( QgsGroupLayer *groupLayer = group->groupLayer() )
            {
                QgsProject::instance()->removeMapLayer( groupLayer );
            }
        }
        QgsLayerTreeGroup *parentGroup = qobject_cast<QgsLayerTreeGroup *>( node->parent() );
        if ( parentGroup )
            parentGroup->removeChildNode( node );
    }
    mapCanvas->refresh();
}

//布局设置
void MainWindow::slot_save_layout()
{
    setting->setValue("LAYOUT/geometry",saveGeometry());//保存QDockWidget类成员的形状和大小
    setting->setValue("LAYOUT/state",saveState());//保存QDockWidget类成员的状态有的
    setting->sync();//立刻写入磁盘文件中
}

void MainWindow::slot_restart_layout()
{
    //下面读取形状大小和读取状态可以选择一个读取,根据喜好可以注释一行
    restoreGeometry(setting->value("LAYOUT/geometry").toByteArray());
    restoreState(setting->value("LAYOUT/state").toByteArray());

    QList<QDockWidget* > dwList = this->findChildren<QDockWidget*>();
    foreach(QDockWidget* dw,dwList){
        restoreDockWidget(dw);
    }
}




void MainWindow::on_action3dtest_triggered()
{
    // 让用户选择图层文件
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Layer"), "", tr("All Files (*);;Shapefiles (*.shp)"));

    if (fileName.isEmpty())
    {
        QMessageBox::warning(this, tr("Layer Error"), tr("No layer selected!"));
        return;
    }


    // 创建图层
    QgsRasterLayer* rasterLayer = new QgsRasterLayer(fileName, "gdal");

    // 检查图层是否有效
    if (!rasterLayer->isValid())
    {
        QMessageBox::warning(this, tr("Layer Error"), tr("The layer is not valid!"));
        delete rasterLayer; // 清理无效图层
        return;
    }

    // 创建 3D 地图画布
    canvas = new Qgs3DMapCanvas();

    // 使用 Qgs3DMapCanvas 实例创建 QgsWindow3DEngine
    engine = new QgsWindow3DEngine(canvas);

    // 创建 3D 地图设置
    Qgs3DMapSettings *mapSettings = new Qgs3DMapSettings();
    mapSettings->setCrs(QgsCoordinateReferenceSystem("EPSG:4326")); // 设置坐标参考系统
    mapSettings->setExtent(QgsRectangle(-180, -90, 180, 90)); // 设置视图范围
    mapSettings->setBackgroundColor(QColor(255, 255, 255)); // 设置背景颜色为白色

    // 确保 rasterLayer 已正确初始化
    if (rasterLayer && rasterLayer->isValid()) {
        mapSettings->setLayers({rasterLayer});  // 添加图层到地图设置
    } else {
        qDebug() << "Raster layer is invalid or not initialized.";
    }

    // 创建 3D 场景，传递地图设置和引擎
    scene = new Qgs3DMapScene(*mapSettings, engine);

    // 设置根实体到引擎
    engine->setRootEntity(scene);

    // canvas->show();
    // // 将 3D 地图画布放入一个 QWidget 中
    // widget = new QWidget();
    // QVBoxLayout *layout = new QVBoxLayout(widget);
    // layout->addWidget(QWidget::createWindowContainer(canvas));

    // // 添加到 tabWidget
    // tabWidget->addTab(widget, u8"3D 视图");

    // 配置画布
    canvas->setMapSettings(mapSettings);

    // 你可以在此处设置相机视角等
    canvas->resetView(); // 重置视角

    scene->viewZoomFull();  // 使相机调整到适合的视角

    canvas->show();
}

