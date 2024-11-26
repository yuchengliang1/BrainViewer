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
#include <QtWidgets/QListWidget>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NiiViewer
{
public:
    QListWidget *listWidget;
    QWidget *widget;
    QOpenGLWidget *openGLWidget;
    QOpenGLWidget *openGLWidget_2;
    QOpenGLWidget *openGLWidget_3;
    QOpenGLWidget *openGLWidget_4;

    void setupUi(QWidget *NiiViewer)
    {
        if (NiiViewer->objectName().isEmpty())
            NiiViewer->setObjectName(QString::fromUtf8("NiiViewer"));
        NiiViewer->resize(1200, 1000);
        listWidget = new QListWidget(NiiViewer);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 200, 1000));
        widget = new QWidget(NiiViewer);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(200, 0, 1000, 1000));
        openGLWidget = new QOpenGLWidget(widget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(25, 25, 450, 450));
        openGLWidget_2 = new QOpenGLWidget(widget);
        openGLWidget_2->setObjectName(QString::fromUtf8("openGLWidget_2"));
        openGLWidget_2->setGeometry(QRect(525, 25, 450, 450));
        openGLWidget_3 = new QOpenGLWidget(widget);
        openGLWidget_3->setObjectName(QString::fromUtf8("openGLWidget_3"));
        openGLWidget_3->setGeometry(QRect(25, 525, 450, 450));
        openGLWidget_4 = new QOpenGLWidget(widget);
        openGLWidget_4->setObjectName(QString::fromUtf8("openGLWidget_4"));
        openGLWidget_4->setGeometry(QRect(525, 525, 450, 450));

        retranslateUi(NiiViewer);

        QMetaObject::connectSlotsByName(NiiViewer);
    } // setupUi

    void retranslateUi(QWidget *NiiViewer)
    {
        NiiViewer->setWindowTitle(QCoreApplication::translate("NiiViewer", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NiiViewer: public Ui_NiiViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NIIVIEWER_H
