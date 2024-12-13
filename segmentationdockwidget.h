#ifndef SEGMENTATIONDOCKWIDGET_H
#define SEGMENTATIONDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
class SegmentationDockWidget;
}
class MainWindow;

class SegmentationDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit SegmentationDockWidget(MainWindow* mainWindow,QWidget *parent = nullptr);
    ~SegmentationDockWidget();

private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_selectUpl_clicked();

    void on_pushButton_selectSvg_clicked();

private:
    Ui::SegmentationDockWidget *ui;
    MainWindow* mainWindow;

};

#endif // SEGMENTATIONDOCKWIDGET_H
