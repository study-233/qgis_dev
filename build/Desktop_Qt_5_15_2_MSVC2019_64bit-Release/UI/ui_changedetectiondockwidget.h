/********************************************************************************
** Form generated from reading UI file 'changedetectiondockwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEDETECTIONDOCKWIDGET_H
#define UI_CHANGEDETECTIONDOCKWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChangeDetectionDockWidget
{
public:
    QWidget *dockWidgetContents;
    QHBoxLayout *horizontalLayout_7;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QLabel *label_13;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_img1;
    QPushButton *pushButton_select1;
    QLabel *label_15;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEdit_img2;
    QPushButton *pushButton_select2;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEdit_svgPath;
    QPushButton *pushButton_selectSvg;
    QLabel *label_12;
    QLineEdit *lineEdit_svgName;
    QLabel *label_14;
    QLineEdit *lineEdit_svgInf;
    QHBoxLayout *horizontalLayout_2;
    QProgressBar *progressBar;
    QPushButton *pushButton_start;
    QPushButton *pushButton_cancel;

    void setupUi(QDockWidget *ChangeDetectionDockWidget)
    {
        if (ChangeDetectionDockWidget->objectName().isEmpty())
            ChangeDetectionDockWidget->setObjectName(QString::fromUtf8("ChangeDetectionDockWidget"));
        ChangeDetectionDockWidget->resize(590, 603);
        ChangeDetectionDockWidget->setMinimumSize(QSize(590, 600));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        horizontalLayout_7 = new QHBoxLayout(dockWidgetContents);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        frame = new QFrame(dockWidgetContents);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_13 = new QLabel(frame);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(12);
        label_13->setFont(font);

        verticalLayout->addWidget(label_13);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit_img1 = new QLineEdit(frame);
        lineEdit_img1->setObjectName(QString::fromUtf8("lineEdit_img1"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_img1->sizePolicy().hasHeightForWidth());
        lineEdit_img1->setSizePolicy(sizePolicy1);
        lineEdit_img1->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(lineEdit_img1);

        pushButton_select1 = new QPushButton(frame);
        pushButton_select1->setObjectName(QString::fromUtf8("pushButton_select1"));
        pushButton_select1->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(pushButton_select1);


        verticalLayout->addLayout(horizontalLayout);

        label_15 = new QLabel(frame);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        sizePolicy.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy);
        label_15->setFont(font);

        verticalLayout->addWidget(label_15);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lineEdit_img2 = new QLineEdit(frame);
        lineEdit_img2->setObjectName(QString::fromUtf8("lineEdit_img2"));
        sizePolicy1.setHeightForWidth(lineEdit_img2->sizePolicy().hasHeightForWidth());
        lineEdit_img2->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(lineEdit_img2);

        pushButton_select2 = new QPushButton(frame);
        pushButton_select2->setObjectName(QString::fromUtf8("pushButton_select2"));

        horizontalLayout_4->addWidget(pushButton_select2);


        verticalLayout->addLayout(horizontalLayout_4);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setFont(font);

        verticalLayout->addWidget(label);

        comboBox = new QComboBox(frame);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout->addWidget(comboBox);

        label_10 = new QLabel(frame);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);
        label_10->setFont(font);

        verticalLayout->addWidget(label_10);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lineEdit_svgPath = new QLineEdit(frame);
        lineEdit_svgPath->setObjectName(QString::fromUtf8("lineEdit_svgPath"));
        sizePolicy1.setHeightForWidth(lineEdit_svgPath->sizePolicy().hasHeightForWidth());
        lineEdit_svgPath->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(lineEdit_svgPath);

        pushButton_selectSvg = new QPushButton(frame);
        pushButton_selectSvg->setObjectName(QString::fromUtf8("pushButton_selectSvg"));

        horizontalLayout_3->addWidget(pushButton_selectSvg);


        verticalLayout->addLayout(horizontalLayout_3);

        label_12 = new QLabel(frame);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        sizePolicy.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy);
        label_12->setFont(font);

        verticalLayout->addWidget(label_12);

        lineEdit_svgName = new QLineEdit(frame);
        lineEdit_svgName->setObjectName(QString::fromUtf8("lineEdit_svgName"));
        sizePolicy1.setHeightForWidth(lineEdit_svgName->sizePolicy().hasHeightForWidth());
        lineEdit_svgName->setSizePolicy(sizePolicy1);
        lineEdit_svgName->setMinimumSize(QSize(160, 20));
        lineEdit_svgName->setMaximumSize(QSize(150, 16777215));

        verticalLayout->addWidget(lineEdit_svgName);

        label_14 = new QLabel(frame);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy);
        label_14->setFont(font);

        verticalLayout->addWidget(label_14);

        lineEdit_svgInf = new QLineEdit(frame);
        lineEdit_svgInf->setObjectName(QString::fromUtf8("lineEdit_svgInf"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit_svgInf->sizePolicy().hasHeightForWidth());
        lineEdit_svgInf->setSizePolicy(sizePolicy2);
        lineEdit_svgInf->setMinimumSize(QSize(550, 90));
        lineEdit_svgInf->setMaximumSize(QSize(0, 120));

        verticalLayout->addWidget(lineEdit_svgInf);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        progressBar = new QProgressBar(frame);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        sizePolicy1.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy1);
        progressBar->setMinimumSize(QSize(0, 0));
        progressBar->setValue(24);

        horizontalLayout_2->addWidget(progressBar);

        pushButton_start = new QPushButton(frame);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));
        sizePolicy.setHeightForWidth(pushButton_start->sizePolicy().hasHeightForWidth());
        pushButton_start->setSizePolicy(sizePolicy);
        pushButton_start->setMinimumSize(QSize(100, 0));

        horizontalLayout_2->addWidget(pushButton_start);

        pushButton_cancel = new QPushButton(frame);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));
        pushButton_cancel->setMinimumSize(QSize(100, 0));

        horizontalLayout_2->addWidget(pushButton_cancel);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_7->addWidget(frame);

        ChangeDetectionDockWidget->setWidget(dockWidgetContents);

        retranslateUi(ChangeDetectionDockWidget);

        QMetaObject::connectSlotsByName(ChangeDetectionDockWidget);
    } // setupUi

    void retranslateUi(QDockWidget *ChangeDetectionDockWidget)
    {
        ChangeDetectionDockWidget->setWindowTitle(QCoreApplication::translate("ChangeDetectionDockWidget", "DockWidget", nullptr));
        label_13->setText(QCoreApplication::translate("ChangeDetectionDockWidget", "\346\227\266\347\233\2701 \345\233\276\345\203\217\346\240\267\346\234\254\357\274\232", nullptr));
        lineEdit_img1->setText(QString());
        pushButton_select1->setText(QCoreApplication::translate("ChangeDetectionDockWidget", "\346\265\217\350\247\210...", nullptr));
        label_15->setText(QCoreApplication::translate("ChangeDetectionDockWidget", "\346\227\266\347\233\2702 \345\233\276\345\203\217\346\240\267\346\234\254\357\274\232", nullptr));
        pushButton_select2->setText(QCoreApplication::translate("ChangeDetectionDockWidget", "\346\265\217\350\247\210...", nullptr));
        label->setText(QCoreApplication::translate("ChangeDetectionDockWidget", "\351\242\204\346\265\213\346\250\241\345\236\213\357\274\232", nullptr));
        label_10->setText(QCoreApplication::translate("ChangeDetectionDockWidget", "\351\242\204\346\265\213\347\273\223\346\236\234\345\255\230\345\202\250\344\275\215\347\275\256 :", nullptr));
        lineEdit_svgPath->setText(QString());
        pushButton_selectSvg->setText(QCoreApplication::translate("ChangeDetectionDockWidget", "\346\265\217\350\247\210...", nullptr));
        label_12->setText(QCoreApplication::translate("ChangeDetectionDockWidget", "\351\242\204\346\265\213\347\273\223\346\236\234\345\220\215\347\247\260 :", nullptr));
        lineEdit_svgName->setText(QString());
        label_14->setText(QCoreApplication::translate("ChangeDetectionDockWidget", "\351\227\256\351\242\230\346\217\217\350\277\260 :", nullptr));
        lineEdit_svgInf->setText(QString());
        pushButton_start->setText(QCoreApplication::translate("ChangeDetectionDockWidget", "\345\274\200\345\247\213", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("ChangeDetectionDockWidget", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangeDetectionDockWidget: public Ui_ChangeDetectionDockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEDETECTIONDOCKWIDGET_H
