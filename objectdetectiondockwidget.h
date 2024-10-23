#ifndef OBJECTDETECTIONDOCKWIDGET_H
#define OBJECTDETECTIONDOCKWIDGET_H

#include <QDockWidget>


namespace Ui {
class ObjectDetectionDockWidget;
}

class MainWindow;

class ObjectDetectionDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit ObjectDetectionDockWidget(MainWindow* mainWindow,QWidget *parent = nullptr);
    ~ObjectDetectionDockWidget();

private slots:
    void on_pushButton_selectUpl_clicked();

    void on_pushButton_selectSvg_clicked();

private:
    Ui::ObjectDetectionDockWidget *ui;

};

#endif // OBJECTDETECTIONDOCKWIDGET_H
