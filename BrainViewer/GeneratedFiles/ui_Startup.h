/********************************************************************************
** Form generated from reading UI file 'Startup.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTUP_H
#define UI_STARTUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Startup
{
public:

    void setupUi(QWidget *Startup)
    {
        if (Startup->objectName().isEmpty())
            Startup->setObjectName(QString::fromUtf8("Startup"));
        Startup->setEnabled(true);
        Startup->resize(660, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Startup->sizePolicy().hasHeightForWidth());
        Startup->setSizePolicy(sizePolicy);
        Startup->setMinimumSize(QSize(660, 300));
        Startup->setMaximumSize(QSize(660, 300));
        Startup->setStyleSheet(QString::fromUtf8("image: url(:/BrainViewer/Resources/brainSightStart.png);"));

        retranslateUi(Startup);

        QMetaObject::connectSlotsByName(Startup);
    } // setupUi

    void retranslateUi(QWidget *Startup)
    {
        Startup->setWindowTitle(QCoreApplication::translate("Startup", "Startup", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Startup: public Ui_Startup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTUP_H
