/********************************************************************************
** Form generated from reading UI file 'transformslider.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSFORMSLIDER_H
#define UI_TRANSFORMSLIDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_transformSlider
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *SlidersGroupBox;
    QGridLayout *gridLayout;
    QLabel *LRLabel;
    QSlider *LRSlider;
    QLabel *PALabel;
    QSlider *PASlider;
    QLabel *ISLabel;
    QSlider *ISSlider;
    QWidget *MinMaxWidget;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *MinLabel;
    QDoubleSpinBox *MinValueSpinBox;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *MaxLabel;
    QDoubleSpinBox *MaxValueSpinBox;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *transformSlider)
    {
        if (transformSlider->objectName().isEmpty())
            transformSlider->setObjectName(QString::fromUtf8("transformSlider"));
        transformSlider->resize(216, 143);
        verticalLayout = new QVBoxLayout(transformSlider);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        SlidersGroupBox = new QWidget(transformSlider);
        SlidersGroupBox->setObjectName(QString::fromUtf8("SlidersGroupBox"));
        gridLayout = new QGridLayout(SlidersGroupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        LRLabel = new QLabel(SlidersGroupBox);
        LRLabel->setObjectName(QString::fromUtf8("LRLabel"));
        LRLabel->setFixedWidth(50);
        gridLayout->addWidget(LRLabel, 0, 0, 1, 1);

        LRSlider = new QSlider(Qt::Horizontal, SlidersGroupBox);
        LRSlider->setObjectName(QString::fromUtf8("LRSlider"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LRSlider->sizePolicy().hasHeightForWidth());
        LRSlider->setSizePolicy(sizePolicy);
        LRSlider->setMinimum(-200.000000000000000);
        LRSlider->setMaximum(200.000000000000000);

        gridLayout->addWidget(LRSlider, 0, 1, 1, 1);

        PALabel = new QLabel(SlidersGroupBox);
        PALabel->setObjectName(QString::fromUtf8("PALabel"));
        PALabel->setFixedWidth(50);

        gridLayout->addWidget(PALabel, 1, 0, 1, 1);

        PASlider = new QSlider(Qt::Horizontal, SlidersGroupBox);
        PASlider->setObjectName(QString::fromUtf8("PASlider"));
        sizePolicy.setHeightForWidth(PASlider->sizePolicy().hasHeightForWidth());
        PASlider->setSizePolicy(sizePolicy);
        PASlider->setMinimum(-200.000000000000000);
        PASlider->setMaximum(200.000000000000000);

        gridLayout->addWidget(PASlider, 1, 1, 1, 1);
        ISLabel = new QLabel(SlidersGroupBox);
        ISLabel->setObjectName(QString::fromUtf8("ISLabel"));
        ISLabel->setFixedWidth(50);

        gridLayout->addWidget(ISLabel, 2, 0, 1, 1);

        ISSlider = new QSlider(Qt::Horizontal, SlidersGroupBox);
        ISSlider->setObjectName(QString::fromUtf8("ISSlider"));
        sizePolicy.setHeightForWidth(ISSlider->sizePolicy().hasHeightForWidth());
        ISSlider->setSizePolicy(sizePolicy);
        ISSlider->setMinimum(-200.000000000000000);
        ISSlider->setMaximum(200.000000000000000);

        gridLayout->addWidget(ISSlider, 2, 1, 1, 1);

        MinMaxWidget = new QWidget(SlidersGroupBox);
        MinMaxWidget->setObjectName(QString::fromUtf8("MinMaxWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(MinMaxWidget->sizePolicy().hasHeightForWidth());
        MinMaxWidget->setSizePolicy(sizePolicy1);
        horizontalLayout_3 = new QHBoxLayout(MinMaxWidget);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        MinLabel = new QLabel(MinMaxWidget);
        MinLabel->setObjectName(QString::fromUtf8("MinLabel"));

        horizontalLayout_2->addWidget(MinLabel);

        MinValueSpinBox = new QDoubleSpinBox(MinMaxWidget);
        MinValueSpinBox->setObjectName(QString::fromUtf8("MinValueSpinBox"));
        sizePolicy.setHeightForWidth(MinValueSpinBox->sizePolicy().hasHeightForWidth());
        MinValueSpinBox->setSizePolicy(sizePolicy);
        MinValueSpinBox->setMinimum(-1000000000.000000000000000);
        MinValueSpinBox->setValue(-200.000000000000000);

        horizontalLayout_2->addWidget(MinValueSpinBox);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        MaxLabel = new QLabel(MinMaxWidget);
        MaxLabel->setObjectName(QString::fromUtf8("MaxLabel"));

        horizontalLayout->addWidget(MaxLabel);

        MaxValueSpinBox = new QDoubleSpinBox(MinMaxWidget);
        MaxValueSpinBox->setObjectName(QString::fromUtf8("MaxValueSpinBox"));
        sizePolicy.setHeightForWidth(MaxValueSpinBox->sizePolicy().hasHeightForWidth());
        MaxValueSpinBox->setSizePolicy(sizePolicy);
        MaxValueSpinBox->setMinimum(-1000000000.000000000000000);
        MaxValueSpinBox->setMaximum(1000000000.000000000000000);
        MaxValueSpinBox->setValue(200.000000000000000);

        horizontalLayout->addWidget(MaxValueSpinBox);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        gridLayout->addWidget(MinMaxWidget, 3, 0, 1, 2);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout->addItem(verticalSpacer, 4, 0, 1, 2);


        verticalLayout->addWidget(SlidersGroupBox);


        retranslateUi(transformSlider);

        QMetaObject::connectSlotsByName(transformSlider);
    } // setupUi

    void retranslateUi(QWidget *transformSlider)
    {
        transformSlider->setWindowTitle(QCoreApplication::translate("transformSlider", "Transform", nullptr));
#if QT_CONFIG(tooltip)
        LRLabel->setToolTip(QCoreApplication::translate("transformSlider", "Left-Right", nullptr));
#endif // QT_CONFIG(tooltip)
        LRLabel->setText(QCoreApplication::translate("transformSlider", "LR", nullptr));
#if QT_CONFIG(tooltip)
        LRSlider->setToolTip(QCoreApplication::translate("transformSlider", "L<-->R", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        PALabel->setToolTip(QCoreApplication::translate("transformSlider", "Posterior-Anterior", nullptr));
#endif // QT_CONFIG(tooltip)
        PALabel->setText(QCoreApplication::translate("transformSlider", "PA", nullptr));
#if QT_CONFIG(tooltip)
        PASlider->setToolTip(QCoreApplication::translate("transformSlider", "P<-->A", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        ISLabel->setToolTip(QCoreApplication::translate("transformSlider", "Inferior-Superior", nullptr));
#endif // QT_CONFIG(tooltip)
        ISLabel->setText(QCoreApplication::translate("transformSlider", "IS", nullptr));
#if QT_CONFIG(tooltip)
        ISSlider->setToolTip(QCoreApplication::translate("transformSlider", "I<-->S", nullptr));
#endif // QT_CONFIG(tooltip)
        MinLabel->setText(QCoreApplication::translate("transformSlider", "Min", nullptr));
        MaxLabel->setText(QCoreApplication::translate("transformSlider", "Max", nullptr));
    } // retranslateUi

};

namespace Ui {
    class transformSlider: public Ui_transformSlider {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSFORMSLIDER_H
