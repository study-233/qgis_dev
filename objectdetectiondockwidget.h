#ifndef OBJECTDETECTIONDOCKWIDGET_H
#define OBJECTDETECTIONDOCKWIDGET_H

#include <QDockWidget>

// 避免直接包含 objectdetectionwork.h
class ObjectDetectionwork;  // 前向声明
class MainWindow;

namespace Ui {
class ObjectDetectionDockWidget;
}

class ObjectDetectionDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit ObjectDetectionDockWidget(MainWindow* mainWindow,QWidget *parent = nullptr);
    ~ObjectDetectionDockWidget();

private slots:
    void on_pushButton_selectUpl_clicked();

    void on_pushButton_selectSvg_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::ObjectDetectionDockWidget *ui;
    MainWindow* mainWindow;
    ObjectDetectionwork* worker = nullptr;
    QTimer *timer;
};

#endif // OBJECTDETECTIONDOCKWIDGET_H
