/********************************************************************************
** Form generated from reading UI file 'reconstructiondockwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECONSTRUCTIONDOCKWIDGET_H
#define UI_RECONSTRUCTIONDOCKWIDGET_H

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

class Ui_ReconstructionDockWidget
{
public:
    QWidget *dockWidgetContents;
    QHBoxLayout *horizontalLayout_5;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QLabel *label_16;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_img;
    QPushButton *pushButton_selectUpl;
    QLabel *label_17;
    QHBoxLayout *horizontalLayout_4;
    QComboBox *comboBox;
    QLabel *label_11;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEdit_svgPath;
    QPushButton *pushButton_selectSvg;
    QLabel *label_18;
    QLineEdit *lineEdit_svgName;
    QLabel *label_19;
    QLineEdit *lineEdit_svgInf_2;
    QHBoxLayout *horizontalLayout_2;
    QProgressBar *progressBar;
    QPushButton *pushButton_start;
    QPushButton *pushButton_cancel;

    void setupUi(QDockWidget *ReconstructionDockWidget)
    {
        if (ReconstructionDockWidget->objectName().isEmpty())
            ReconstructionDockWidget->setObjectName(QString::fromUtf8("ReconstructionDockWidget"));
        ReconstructionDockWidget->resize(590, 600);
        ReconstructionDockWidget->setMinimumSize(QSize(590, 600));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        horizontalLayout_5 = new QHBoxLayout(dockWidgetContents);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        frame = new QFrame(dockWidgetContents);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_16 = new QLabel(frame);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(12);
        label_16->setFont(font);

        verticalLayout->addWidget(label_16);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit_img = new QLineEdit(frame);
        lineEdit_img->setObjectName(QString::fromUtf8("lineEdit_img"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_img->sizePolicy().hasHeightForWidth());
        lineEdit_img->setSizePolicy(sizePolicy1);
        lineEdit_img->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(lineEdit_img);

        pushButton_selectUpl = new QPushButton(frame);
        pushButton_selectUpl->setObjectName(QString::fromUtf8("pushButton_selectUpl"));
        pushButton_selectUpl->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(pushButton_selectUpl);


        verticalLayout->addLayout(horizontalLayout);

        label_17 = new QLabel(frame);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        sizePolicy.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy);
        label_17->setFont(font);

        verticalLayout->addWidget(label_17);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        comboBox = new QComboBox(frame);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout_4);

        label_11 = new QLabel(frame);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);
        label_11->setFont(font);

        verticalLayout->addWidget(label_11);

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

        label_18 = new QLabel(frame);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        sizePolicy.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy);
        label_18->setFont(font);

        verticalLayout->addWidget(label_18);

        lineEdit_svgName = new QLineEdit(frame);
        lineEdit_svgName->setObjectName(QString::fromUtf8("lineEdit_svgName"));
        sizePolicy1.setHeightForWidth(lineEdit_svgName->sizePolicy().hasHeightForWidth());
        lineEdit_svgName->setSizePolicy(sizePolicy1);
        lineEdit_svgName->setMinimumSize(QSize(160, 20));
        lineEdit_svgName->setMaximumSize(QSize(150, 16777215));

        verticalLayout->addWidget(lineEdit_svgName);

        label_19 = new QLabel(frame);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        sizePolicy.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy);
        label_19->setFont(font);

        verticalLayout->addWidget(label_19);

        lineEdit_svgInf_2 = new QLineEdit(frame);
        lineEdit_svgInf_2->setObjectName(QString::fromUtf8("lineEdit_svgInf_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit_svgInf_2->sizePolicy().hasHeightForWidth());
        lineEdit_svgInf_2->setSizePolicy(sizePolicy2);
        lineEdit_svgInf_2->setMinimumSize(QSize(550, 90));
        lineEdit_svgInf_2->setMaximumSize(QSize(0, 120));

        verticalLayout->addWidget(lineEdit_svgInf_2);

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


        horizontalLayout_5->addWidget(frame);

        ReconstructionDockWidget->setWidget(dockWidgetContents);

        retranslateUi(ReconstructionDockWidget);

        QMetaObject::connectSlotsByName(ReconstructionDockWidget);
    } // setupUi

    void retranslateUi(QDockWidget *ReconstructionDockWidget)
    {
        ReconstructionDockWidget->setWindowTitle(QCoreApplication::translate("ReconstructionDockWidget", "DockWidget", nullptr));
        label_16->setText(QCoreApplication::translate("ReconstructionDockWidget", "\344\275\216\350\264\250\345\233\276\345\203\217\346\240\267\346\234\254\357\274\232", nullptr));
        lineEdit_img->setText(QString());
        pushButton_selectUpl->setText(QCoreApplication::translate("ReconstructionDockWidget", "\346\265\217\350\247\210...", nullptr));
        label_17->setText(QCoreApplication::translate("ReconstructionDockWidget", "\351\242\204\346\265\213\346\250\241\345\236\213\357\274\232", nullptr));
        label_11->setText(QCoreApplication::translate("ReconstructionDockWidget", "\351\242\204\346\265\213\347\273\223\346\236\234\345\255\230\345\202\250\344\275\215\347\275\256 :", nullptr));
        pushButton_selectSvg->setText(QCoreApplication::translate("ReconstructionDockWidget", "\346\265\217\350\247\210...", nullptr));
        label_18->setText(QCoreApplication::translate("ReconstructionDockWidget", "\351\242\204\346\265\213\347\273\223\346\236\234\345\220\215\347\247\260 :", nullptr));
        lineEdit_svgName->setText(QString());
        label_19->setText(QCoreApplication::translate("ReconstructionDockWidget", "\351\227\256\351\242\230\346\217\217\350\277\260 :", nullptr));
        lineEdit_svgInf_2->setText(QString());
        pushButton_start->setText(QCoreApplication::translate("ReconstructionDockWidget", "\345\274\200\345\247\213", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("ReconstructionDockWidget", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReconstructionDockWidget: public Ui_ReconstructionDockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECONSTRUCTIONDOCKWIDGET_H
