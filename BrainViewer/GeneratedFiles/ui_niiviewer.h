/********************************************************************************
** Form generated from reading UI file 'niiviewer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NIIVIEWER_H
#define UI_NIIVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_NiiViewer
{
public:
    QWidget *toolBoxList;
    QWidget *viewerWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QVTKWidget *sagittalViewPanel;
    QVTKWidget *coronalViewPanel;
    QVTKWidget *transverseViewPanel;
    QVTKWidget *View3DPanel;

    void setupUi(QWidget *NiiViewer)
    {
        if (NiiViewer->objectName().isEmpty())
            NiiViewer->setObjectName(QString::fromUtf8("NiiViewer"));
        // NiiViewer->resize(1200, 1000);

        toolBoxList = new QWidget(NiiViewer);
        toolBoxList->setObjectName(QString::fromUtf8("toolBoxList"));
        toolBoxList->setFixedWidth(450);

        gridLayoutWidget = new QWidget(NiiViewer);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));

        QHBoxLayout* hboxLayout = new QHBoxLayout(NiiViewer);
        hboxLayout->addWidget(toolBoxList);
        hboxLayout->addWidget(gridLayoutWidget);
        hboxLayout->setStretchFactor(gridLayoutWidget, 1);

        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(5, 5, 5, 5);

        sagittalViewPanel = new QVTKWidget(gridLayoutWidget);
        sagittalViewPanel->setObjectName(QString::fromUtf8("sagittalViewPanel"));
        sagittalViewPanel->setMinimumSize(QSize(510, 490));
        gridLayout->addWidget(sagittalViewPanel, 0, 0);

        
        coronalViewPanel = new QVTKWidget(gridLayoutWidget);
        coronalViewPanel->setObjectName(QString::fromUtf8("coronalViewPanel"));
        coronalViewPanel->setMinimumSize(QSize(510, 490));
        gridLayout->addWidget(coronalViewPanel, 0, 1);

        transverseViewPanel = new QVTKWidget(gridLayoutWidget);
        transverseViewPanel->setObjectName(QString::fromUtf8("transverseViewPanel"));
        transverseViewPanel->setMinimumSize(QSize(510, 490));
        gridLayout->addWidget(transverseViewPanel, 1, 0);

        View3DPanel = new QVTKWidget(gridLayoutWidget);
        View3DPanel->setObjectName(QString::fromUtf8("View3DPanel"));
        View3DPanel->setMinimumSize(QSize(510, 490));
        gridLayout->addWidget(View3DPanel, 1, 1);

        retranslateUi(NiiViewer);
        QMetaObject::connectSlotsByName(NiiViewer);
    } // setupUi

    void retranslateUi(QWidget *NiiViewer)
    {
        NiiViewer->setWindowTitle(QCoreApplication::translate("NiiViewer", "BrainViewer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NiiViewer: public Ui_NiiViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NIIVIEWER_H
