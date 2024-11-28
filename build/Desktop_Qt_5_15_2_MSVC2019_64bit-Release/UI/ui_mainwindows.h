/********************************************************************************
** Form generated from reading UI file 'mainwindows.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWS_H
#define UI_MAINWINDOWS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_raster;
    QAction *actionOpen_vector;
    QAction *actionRemove_file;
    QAction *actionAbout;
    QAction *actionSegmentation;
    QAction *actionImport_mask;
    QAction *action3dtest;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QMenu *menuTool;
    QMenu *menuSetting;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(837, 618);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        actionOpen_raster = new QAction(MainWindow);
        actionOpen_raster->setObjectName(QString::fromUtf8("actionOpen_raster"));
        actionOpen_vector = new QAction(MainWindow);
        actionOpen_vector->setObjectName(QString::fromUtf8("actionOpen_vector"));
        actionRemove_file = new QAction(MainWindow);
        actionRemove_file->setObjectName(QString::fromUtf8("actionRemove_file"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionSegmentation = new QAction(MainWindow);
        actionSegmentation->setObjectName(QString::fromUtf8("actionSegmentation"));
        actionImport_mask = new QAction(MainWindow);
        actionImport_mask->setObjectName(QString::fromUtf8("actionImport_mask"));
        action3dtest = new QAction(MainWindow);
        action3dtest->setObjectName(QString::fromUtf8("action3dtest"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 837, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuTool = new QMenu(menubar);
        menuTool->setObjectName(QString::fromUtf8("menuTool"));
        menuSetting = new QMenu(menubar);
        menuSetting->setObjectName(QString::fromUtf8("menuSetting"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuTool->menuAction());
        menubar->addAction(menuSetting->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen_raster);
        menuFile->addAction(actionOpen_vector);
        menuFile->addAction(actionRemove_file);
        menuFile->addAction(actionImport_mask);
        menuFile->addAction(action3dtest);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QString());
        actionOpen_raster->setText(QCoreApplication::translate("MainWindow", "Open raster", nullptr));
        actionOpen_vector->setText(QCoreApplication::translate("MainWindow", "Open vector", nullptr));
        actionRemove_file->setText(QCoreApplication::translate("MainWindow", "Remove file", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionSegmentation->setText(QCoreApplication::translate("MainWindow", "Segmentation", nullptr));
        actionImport_mask->setText(QCoreApplication::translate("MainWindow", "Import mask", nullptr));
#if QT_CONFIG(tooltip)
        actionImport_mask->setToolTip(QCoreApplication::translate("MainWindow", "Import mask", nullptr));
#endif // QT_CONFIG(tooltip)
        action3dtest->setText(QCoreApplication::translate("MainWindow", "3dtest", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
        menuTool->setTitle(QCoreApplication::translate("MainWindow", "Tool", nullptr));
        menuSetting->setTitle(QCoreApplication::translate("MainWindow", "Setting", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWS_H
