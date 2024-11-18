/********************************************************************************
** Form generated from reading UI file 'Register.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_Register
{
public:
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_Ok;
    QRadioButton *radioButton_Multi;
    QRadioButton *radioButton_CenteredSimilarity;
    QPushButton *pushButton_SelectImageFix;
    QLineEdit *lineEdit_ImageFix;
    QRadioButton *radioButton_Translation;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_SelectImageMove;
    QRadioButton *radioButton_Affine;
    QLineEdit *lineEdit_ImageMove;
    QPushButton *pushButton_Cancel;
    QWidget *widget;
    QGridLayout *gridLayout_5;
    QSplitter *splitter_3;
    QSplitter *splitter;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QVTKWidget *qvtkWidget_Registration_UL;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_3;
    QVTKWidget *qvtkWidget_Registration_DL;
    QLabel *label;
    QSplitter *splitter_2;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QVTKWidget *qvtkWidget_Registration_UR;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_4;
    QVTKWidget *qvtkWidget_Registration_DR;
    QLabel *label_4;

    void setupUi(QWidget *Register)
    {
        if (Register->objectName().isEmpty())
            Register->setObjectName(QString::fromUtf8("Register"));
        Register->resize(840, 719);
        Register->setStyleSheet(QString::fromUtf8(""));
        gridLayout_2 = new QGridLayout(Register);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButton_Ok = new QPushButton(Register);
        pushButton_Ok->setObjectName(QString::fromUtf8("pushButton_Ok"));
        pushButton_Ok->setMinimumSize(QSize(100, 25));
        pushButton_Ok->setMaximumSize(QSize(100, 25));

        gridLayout_2->addWidget(pushButton_Ok, 0, 7, 1, 1);

        radioButton_Multi = new QRadioButton(Register);
        radioButton_Multi->setObjectName(QString::fromUtf8("radioButton_Multi"));
        radioButton_Multi->setChecked(false);

        gridLayout_2->addWidget(radioButton_Multi, 2, 5, 1, 1);

        radioButton_CenteredSimilarity = new QRadioButton(Register);
        radioButton_CenteredSimilarity->setObjectName(QString::fromUtf8("radioButton_CenteredSimilarity"));

        gridLayout_2->addWidget(radioButton_CenteredSimilarity, 2, 3, 1, 1);

        pushButton_SelectImageFix = new QPushButton(Register);
        pushButton_SelectImageFix->setObjectName(QString::fromUtf8("pushButton_SelectImageFix"));
        pushButton_SelectImageFix->setMinimumSize(QSize(100, 25));
        pushButton_SelectImageFix->setMaximumSize(QSize(100, 25));

        gridLayout_2->addWidget(pushButton_SelectImageFix, 0, 0, 1, 1);

        lineEdit_ImageFix = new QLineEdit(Register);
        lineEdit_ImageFix->setObjectName(QString::fromUtf8("lineEdit_ImageFix"));
        lineEdit_ImageFix->setMinimumSize(QSize(0, 25));
        lineEdit_ImageFix->setMaximumSize(QSize(16777215, 25));

        gridLayout_2->addWidget(lineEdit_ImageFix, 0, 1, 1, 6);

        radioButton_Translation = new QRadioButton(Register);
        radioButton_Translation->setObjectName(QString::fromUtf8("radioButton_Translation"));
        radioButton_Translation->setChecked(true);

        gridLayout_2->addWidget(radioButton_Translation, 2, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(115, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(115, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 2, 6, 1, 1);

        pushButton_SelectImageMove = new QPushButton(Register);
        pushButton_SelectImageMove->setObjectName(QString::fromUtf8("pushButton_SelectImageMove"));
        pushButton_SelectImageMove->setMinimumSize(QSize(100, 25));
        pushButton_SelectImageMove->setMaximumSize(QSize(100, 25));

        gridLayout_2->addWidget(pushButton_SelectImageMove, 1, 0, 1, 1);

        radioButton_Affine = new QRadioButton(Register);
        radioButton_Affine->setObjectName(QString::fromUtf8("radioButton_Affine"));
        radioButton_Affine->setChecked(false);

        gridLayout_2->addWidget(radioButton_Affine, 2, 4, 1, 1);

        lineEdit_ImageMove = new QLineEdit(Register);
        lineEdit_ImageMove->setObjectName(QString::fromUtf8("lineEdit_ImageMove"));
        lineEdit_ImageMove->setMinimumSize(QSize(0, 25));
        lineEdit_ImageMove->setMaximumSize(QSize(16777215, 25));

        gridLayout_2->addWidget(lineEdit_ImageMove, 1, 1, 1, 6);

        pushButton_Cancel = new QPushButton(Register);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setMinimumSize(QSize(100, 25));
        pushButton_Cancel->setMaximumSize(QSize(100, 25));

        gridLayout_2->addWidget(pushButton_Cancel, 1, 7, 1, 1);

        widget = new QWidget(Register);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout_5 = new QGridLayout(widget);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        splitter_3 = new QSplitter(widget);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        splitter = new QSplitter(splitter_3);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        widget_2 = new QWidget(splitter);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(60, 16));
        label_2->setMaximumSize(QSize(60, 16));

        verticalLayout_2->addWidget(label_2);

        qvtkWidget_Registration_UL = new QVTKWidget(widget_2);
        qvtkWidget_Registration_UL->setObjectName(QString::fromUtf8("qvtkWidget_Registration_UL"));
        qvtkWidget_Registration_UL->setMinimumSize(QSize(340, 255));

        verticalLayout_2->addWidget(qvtkWidget_Registration_UL);

        splitter->addWidget(widget_2);
        widget_3 = new QWidget(splitter);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        verticalLayout_3 = new QVBoxLayout(widget_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        qvtkWidget_Registration_DL = new QVTKWidget(widget_3);
        qvtkWidget_Registration_DL->setObjectName(QString::fromUtf8("qvtkWidget_Registration_DL"));
        qvtkWidget_Registration_DL->setMinimumSize(QSize(340, 255));

        verticalLayout_3->addWidget(qvtkWidget_Registration_DL);

        label = new QLabel(widget_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(60, 16));
        label->setMaximumSize(QSize(60, 16));

        verticalLayout_3->addWidget(label);

        splitter->addWidget(widget_3);
        splitter_3->addWidget(splitter);
        splitter_2 = new QSplitter(splitter_3);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        widget_4 = new QWidget(splitter_2);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        verticalLayout = new QVBoxLayout(widget_4);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_3 = new QLabel(widget_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(60, 16));
        label_3->setMaximumSize(QSize(60, 16));

        verticalLayout->addWidget(label_3);

        qvtkWidget_Registration_UR = new QVTKWidget(widget_4);
        qvtkWidget_Registration_UR->setObjectName(QString::fromUtf8("qvtkWidget_Registration_UR"));
        qvtkWidget_Registration_UR->setMinimumSize(QSize(340, 255));

        verticalLayout->addWidget(qvtkWidget_Registration_UR);

        splitter_2->addWidget(widget_4);
        widget_5 = new QWidget(splitter_2);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        verticalLayout_4 = new QVBoxLayout(widget_5);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        qvtkWidget_Registration_DR = new QVTKWidget(widget_5);
        qvtkWidget_Registration_DR->setObjectName(QString::fromUtf8("qvtkWidget_Registration_DR"));
        qvtkWidget_Registration_DR->setMinimumSize(QSize(340, 255));

        verticalLayout_4->addWidget(qvtkWidget_Registration_DR);

        label_4 = new QLabel(widget_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(60, 16));
        label_4->setMaximumSize(QSize(60, 16));

        verticalLayout_4->addWidget(label_4);

        splitter_2->addWidget(widget_5);
        splitter_3->addWidget(splitter_2);

        gridLayout_5->addWidget(splitter_3, 0, 0, 1, 1);


        gridLayout_2->addWidget(widget, 3, 0, 1, 8);


        retranslateUi(Register);
        QObject::connect(pushButton_SelectImageFix, SIGNAL(clicked()), Register, SLOT(OnSelectImageFix()));
        QObject::connect(pushButton_SelectImageMove, SIGNAL(clicked()), Register, SLOT(OnSelectImageMove()));
        QObject::connect(pushButton_Ok, SIGNAL(clicked()), Register, SLOT(OnButtonOk()));
        QObject::connect(pushButton_Cancel, SIGNAL(clicked()), Register, SLOT(OnButtonCancel()));
        QObject::connect(radioButton_Translation, SIGNAL(clicked()), Register, SLOT(OnSelectTranslation()));
        QObject::connect(radioButton_CenteredSimilarity, SIGNAL(clicked()), Register, SLOT(OnSelectCenteredSimilarity()));
        QObject::connect(radioButton_Affine, SIGNAL(clicked()), Register, SLOT(OnSelectAffine()));
        QObject::connect(radioButton_Multi, SIGNAL(clicked()), Register, SLOT(OnSelectMulit()));

        QMetaObject::connectSlotsByName(Register);
    } // setupUi

    void retranslateUi(QWidget *Register)
    {
        Register->setWindowTitle(QCoreApplication::translate("Register", "\351\205\215\345\207\206\345\267\245\345\205\267", nullptr));
        pushButton_Ok->setText(QCoreApplication::translate("Register", "\345\274\200\345\247\213\350\256\241\347\256\227", nullptr));
        radioButton_Multi->setText(QCoreApplication::translate("Register", "\351\255\224\346\263\225\345\217\230\346\215\242", nullptr));
        radioButton_CenteredSimilarity->setText(QCoreApplication::translate("Register", "\344\270\255\345\277\203\347\233\270\344\274\274\344\272\214\347\273\264\345\217\230\346\215\242", nullptr));
        pushButton_SelectImageFix->setText(QCoreApplication::translate("Register", "\345\237\272\345\207\206\345\233\276\345\203\217", nullptr));
        radioButton_Translation->setText(QCoreApplication::translate("Register", "\345\271\263\347\247\273\345\217\230\346\215\242", nullptr));
        pushButton_SelectImageMove->setText(QCoreApplication::translate("Register", "\345\276\205\351\205\215\345\207\206\345\233\276\345\203\217", nullptr));
        radioButton_Affine->setText(QCoreApplication::translate("Register", "\344\273\277\345\260\204\345\217\230\346\215\242", nullptr));
        pushButton_Cancel->setText(QCoreApplication::translate("Register", "\351\200\200\345\207\272", nullptr));
        label_2->setText(QCoreApplication::translate("Register", "\345\237\272\345\207\206\345\233\276\345\203\217", nullptr));
        label->setText(QCoreApplication::translate("Register", "\344\270\255\351\227\264\347\273\223\346\236\234", nullptr));
        label_3->setText(QCoreApplication::translate("Register", "\345\276\205\351\205\215\345\207\206\345\233\276\345\203\217", nullptr));
        label_4->setText(QCoreApplication::translate("Register", "\346\234\200\347\273\210\347\273\223\346\236\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Register: public Ui_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
