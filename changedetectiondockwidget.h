#ifndef CHANGEDETECTIONDOCKWIDGET_H
#define CHANGEDETECTIONDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
class ChangeDetectionDockWidget;
}

class ChangeDetectionwork;
class MainWindow;

class ChangeDetectionDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit ChangeDetectionDockWidget(MainWindow* mainWindow,QWidget *parent = nullptr);
    ~ChangeDetectionDockWidget();

private slots:
    void on_pushButton_select1_clicked();

    void on_pushButton_select2_clicked();

    void on_pushButton_selectSvg_clicked();

    void on_pushButton_start_clicked();


private:
    Ui::ChangeDetectionDockWidget *ui;
    MainWindow* mainWindow;
    ChangeDetectionwork *worker;
};

#endif // CHANGEDETECTIONDOCKWIDGET_H

