#ifndef RECONSTRUCTIONDOCKWIDGET_H
#define RECONSTRUCTIONDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
class ReconstructionDockWidget;
}
class MainWindow;
class ReconstructionDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit ReconstructionDockWidget(MainWindow* mainWindow, QWidget *parent = nullptr);
    ~ReconstructionDockWidget();

private slots:
    void on_pushButton_selectUpl_clicked();

    void on_pushButton_selectSvg_clicked();

    void on_pushButton_start_clicked();

private:
    Ui::ReconstructionDockWidget *ui;
    MainWindow* mainWindow;
};

#endif // RECONSTRUCTIONDOCKWIDGET_H
