#include "mainwindows.h"
#include "qgis_devlayertreeviewmenuprovider.h"

#include "qgis.h"
#include <QMenu>
#include <QModelIndex>
#include <QIcon>

// QGis include
#include <qgslayertreeviewdefaultactions.h>
#include <qgslayertreenode.h>
#include <qgslayertreemodel.h>
#include <qgslayertree.h>
#include <qgsrasterlayer.h>
#include <qgsvectorlayer.h>
#include "qmainwindow.h"
#include "QWidgetAction"

qgis_devLayerTreeViewMenuProvider::qgis_devLayerTreeViewMenuProvider(QgsLayerTreeView* view, QgsMapCanvas* canvas)
    : m_layerTreeView(view)
    , m_mapCanvas(canvas)
{}
//重写方法获取右键菜单
QMenu* qgis_devLayerTreeViewMenuProvider::createContextMenu()
{
    // 设置这个路径是为了获取图标文件
    QString iconDir = "E:\\QtDocuments\\My_Qgis\\image\\";

    QMenu* menu = new QMenu;
    QgsLayerTreeViewDefaultActions* actions = m_layerTreeView->defaultActions();
    QModelIndex idx = m_layerTreeView->currentIndex();

    // global menu
    if (!idx.isValid())
    {
        menu->addAction(actions->actionAddGroup(menu));
        menu->addAction(QIcon(iconDir + "mActionExpandTree.png"), tr("&Expand All"), m_layerTreeView, SLOT(expandAll()));
        menu->addAction(QIcon(iconDir + "mActionCollapseTree.png"), tr("&Collapse All"), m_layerTreeView, SLOT(collapseAll()));
        menu->addSeparator();

    }

    else if (QgsLayerTreeNode* node=m_layerTreeView->currentNode())
    {
        // layer or group selected
        if (QgsLayerTree::isGroup(node))
        {
            menu->addAction(actions->actionZoomToGroup(m_mapCanvas, menu));
            menu->addAction(actions->actionRemoveGroupOrLayer(menu));
            menu->addAction(actions->actionRenameGroupOrLayer(menu));
            if (m_layerTreeView->selectedNodes(true).count() >= 2)
            {
                menu->addAction(actions->actionGroupSelected(menu));
            }
            menu->addAction(actions->actionAddGroup(menu));
        }
        else if (QgsLayerTree::isLayer(node))
        {
            QgsMapLayer* layer = QgsLayerTree::toLayer(node)->layer();

            if ( layer && layer->isSpatial() )
            {
                //添加zoom to layer右键菜单项目
                QAction *zoomToLayers = actions->actionZoomToLayers(m_mapCanvas, menu );
                zoomToLayers->setEnabled( layer->isValid() );
                menu->addAction(zoomToLayers);
            }

            menu->addAction(actions->actionRemoveGroupOrLayer(menu));

            menu->addAction(QObject::tr("&Label"), MainWindow::instance(), SLOT(slot_labelShowAction()));

            // 如果选择的是矢量图层
            if (layer->type() == Qgis::LayerType::Vector)
            {
                //点矢量图层增加点样式设置菜单
                QgsVectorLayer* veclayer = qobject_cast<QgsVectorLayer*>(layer);
                if (veclayer->geometryType() == Qgis::GeometryType::Point)
                {
                    menu->addAction(QObject::tr("PointStyle"), MainWindow::instance(), SLOT(slot_pointstyle()));
                }
                else if (veclayer->geometryType() == Qgis::GeometryType::Polygon)
                {
                    menu->addAction(QObject::tr("PolygonStyle"), MainWindow::instance(), SLOT(slot_polygonstyle()));
                }
            }

            // 如果选择的是栅格图层
            if (layer && layer->type() == Qgis::LayerType::Raster)
            {
                QgsRasterLayer *rlayer = qobject_cast<QgsRasterLayer *>( layer );

                QAction *zoomToNative = menu->addAction( QIcon(iconDir + "mActionZoomActual.png"), tr( "Zoom to Nat&ive Resolution (100%)" ), MainWindow::instance(), &MainWindow::legendLayerZoomNative );
                zoomToNative->setEnabled( rlayer->isValid() );

            }

            // 添加透明度调整
            QAction* opacityAction = new QAction(tr("Adjust Opacity"), menu);
            QSlider* opacitySlider = new QSlider(Qt::Horizontal, menu);
            opacitySlider->setRange(0, 100);  // 设置透明度范围为0-100%
            opacitySlider->setValue(layer->opacity() * 30);  // 设置初始值为当前图层透明度

            QWidgetAction* sliderAction = new QWidgetAction(menu);
            sliderAction->setDefaultWidget(opacitySlider);
            menu->addAction(sliderAction);

            // 连接滑动条值的变化与图层透明度的设置
            connect(opacitySlider, &QSlider::valueChanged, [layer](int value) {
                layer->setOpacity(value / 100.0);  // 将滑动条的值转换为透明度 (0.0 - 1.0)
                layer->triggerRepaint();  // 重新渲染图层
            });
        }
    }

    return menu;
}



void qgis_devLayerTreeViewMenuProvider::addLegendLayerAction(QAction* action, const QString& menu, QString id, Qgis::LayerType type, bool allLayers)
{

}

void qgis_devLayerTreeViewMenuProvider::addLegendLayerActionForLayer(QAction* action, QgsMapLayer* layer)
{

}

void qgis_devLayerTreeViewMenuProvider::removeLegendLayerActionsForLayer(QgsMapLayer* layer)
{

}

QList< LegendLayerAction > qgis_devLayerTreeViewMenuProvider::legendLayerActions(Qgis::LayerType type) const
{
    return mLegendLayerActionMap.contains(type) ? mLegendLayerActionMap.value(type) : QList<LegendLayerAction>();
}

bool qgis_devLayerTreeViewMenuProvider::removeLegendLayerAction(QAction* action)
{
    QMap< Qgis::LayerType, QList< LegendLayerAction > >::iterator it;
    for (it = mLegendLayerActionMap.begin();
         it != mLegendLayerActionMap.end(); ++it)
    {
        for (int i = 0; i < it->count(); i++)
        {
            if ((*it)[i].action == action)
            {
                (*it).removeAt(i);
                return true;
            }
        }
    }
    return false;
}

void qgis_devLayerTreeViewMenuProvider::addCustomLayerActions(QMenu* menu, QgsMapLayer* layer)
{

}
