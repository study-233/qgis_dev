#ifndef QGIS_DEVLAYERTREEVIEWMENUPROVIDER_H
#define QGIS_DEVLAYERTREEVIEWMENUPROVIDER_H
#include <QObject>                         //QT对象
#include <QtMath>
#include <qgslayertreeview.h>
#include <qgsmaplayer.h>

#include <qgsmapcanvas.h>
#include <qdockwidget.h>
#include <qgslayertree.h>
#include <qgslayertreeviewdefaultactions.h>
#include <qtoolbutton.h>

class QAction;
class QgsMapCanvas;

struct LegendLayerAction
{
    LegendLayerAction(QAction* a, QString m, QString i, bool all)
        : action(a), menu(m), id(i), allLayers(all) {}
    QAction* action = nullptr;
    QString menu;
    QString id;
    bool allLayers;
    QList<QgsMapLayer*> layers;
};


class qgis_devLayerTreeViewMenuProvider : public QObject, public QgsLayerTreeViewMenuProvider
{
public:
    qgis_devLayerTreeViewMenuProvider(QgsLayerTreeView* view, QgsMapCanvas* canvas); // 构造函数这样定义，直接获得图层管理器和地图画布控件，以便对它们建立联系
    ~qgis_devLayerTreeViewMenuProvider() {};

    //! 重写这个方法来获取右键菜单
    QMenu* createContextMenu();

    void addLegendLayerAction(QAction* action, const QString& menu, QString id,
                              Qgis::LayerType type, bool allLayers);
    bool removeLegendLayerAction(QAction* action);
    void addLegendLayerActionForLayer(QAction* action, QgsMapLayer* layer);
    void removeLegendLayerActionsForLayer(QgsMapLayer* layer);
    QList< LegendLayerAction > legendLayerActions(Qgis::LayerType type) const;

protected:

    void addCustomLayerActions(QMenu* menu, QgsMapLayer* layer);

    QgsLayerTreeView* m_layerTreeView = nullptr;;
    QgsMapCanvas* m_mapCanvas = nullptr;

    QMap<Qgis::LayerType, QList< LegendLayerAction>> mLegendLayerActionMap;

};

#endif // QGIS_DEVLAYERTREEVIEWMENUPROVIDER_H
