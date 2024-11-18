/********************************************************************************
** Form generated from reading UI file 'BrainViewer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BRAINVIEWER_H
#define UI_BRAINVIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_BrainViewerClass
{
public:
    QAction *action_OpenSeriesFolder;
    QAction *action_back;
    QAction *action_next;
    QAction *action_Pointer;
    QAction *action_Protractor;
    QAction *action_Ruler;
    QAction *action_Contour;
    QAction *action_BiDimensional;
    QAction *action_Negative;
    QAction *action_Reset;
    QAction *action_Zoom;
    QAction *action_GrayLevel;
    QAction *action_Move;
    QAction *action_SwitchOfProperty;
    QAction *action_Play;
    QAction *action_Stop;
    QAction *action_TestEntrance_01;
    QAction *action_TestEntrance_02;
    QAction *action_OpenDicomDirFile;
    QAction *action_OpenDicomFile;
    QAction *action_PreviousPatient;
    QAction *action_LatterPatient;
    QAction *action_WindowWL_Default;
    QAction *action_WindowWL_All;
    QAction *action_WindowWL_CT_Abdomen;
    QAction *action_WindowWL_CT_BloodVessel;
    QAction *action_WindowWL_CT_Bones;
    QAction *action_WindowWL_CT_Brain;
    QAction *action_WindowWL_CT_Medias;
    QAction *action_WindowWL_CT_Lungs;
    QAction *action_Registration;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVTKWidget *qvtkWidget;
    QScrollBar *SliceScrollBar;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_5;
    QMenu *menu_WindowSizeLevel;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget_Dir;
    QWidget *dockWidgetContents;
    QHBoxLayout *horizontalLayout;
    QTreeView *treeView;

    void setupUi(QMainWindow *BrainViewerClass)
    {
        if (BrainViewerClass->objectName().isEmpty())
            BrainViewerClass->setObjectName(QString::fromUtf8("BrainViewerClass"));
        BrainViewerClass->resize(1200, 738);
        BrainViewerClass->setMinimumSize(QSize(1200, 700));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        BrainViewerClass->setPalette(palette);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/BrainViewer/Resources/brainSightLogo.png"), QSize(), QIcon::Normal, QIcon::Off);
        BrainViewerClass->setWindowIcon(icon);
        BrainViewerClass->setAutoFillBackground(false);
        BrainViewerClass->setStyleSheet(QString::fromUtf8(""));
        action_OpenSeriesFolder = new QAction(BrainViewerClass);
        action_OpenSeriesFolder->setObjectName(QString::fromUtf8("action_OpenSeriesFolder"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/BrainViewer/Resources/folder_128px_1207828_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_OpenSeriesFolder->setIcon(icon1);
        action_back = new QAction(BrainViewerClass);
        action_back->setObjectName(QString::fromUtf8("action_back"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/BrainViewer/Resources/front_128px_1143868_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_back->setIcon(icon2);
        action_next = new QAction(BrainViewerClass);
        action_next->setObjectName(QString::fromUtf8("action_next"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/BrainViewer/Resources/next_128px_1143867_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_next->setIcon(icon3);
        action_Pointer = new QAction(BrainViewerClass);
        action_Pointer->setObjectName(QString::fromUtf8("action_Pointer"));
        action_Pointer->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/BrainViewer/Resources/mouse_128px_1153948_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_Pointer->setIcon(icon4);
        action_Protractor = new QAction(BrainViewerClass);
        action_Protractor->setObjectName(QString::fromUtf8("action_Protractor"));
        action_Protractor->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/BrainViewer/Resources/Angle_Thingy_128px_559411_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_Protractor->setIcon(icon5);
        action_Ruler = new QAction(BrainViewerClass);
        action_Ruler->setObjectName(QString::fromUtf8("action_Ruler"));
        action_Ruler->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/BrainViewer/Resources/ruler_128px_1209146_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_Ruler->setIcon(icon6);
        action_Contour = new QAction(BrainViewerClass);
        action_Contour->setObjectName(QString::fromUtf8("action_Contour"));
        action_Contour->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/BrainViewer/Resources/Bezier_Curve_128px_559452_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_Contour->setIcon(icon7);
        action_BiDimensional = new QAction(BrainViewerClass);
        action_BiDimensional->setObjectName(QString::fromUtf8("action_BiDimensional"));
        action_BiDimensional->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/BrainViewer/Resources/Arrow_Cross_128px_1177075_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_BiDimensional->setIcon(icon8);
        action_Negative = new QAction(BrainViewerClass);
        action_Negative->setObjectName(QString::fromUtf8("action_Negative"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/BrainViewer/Resources/video_negative_128px_1138773_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_Negative->setIcon(icon9);
        action_Reset = new QAction(BrainViewerClass);
        action_Reset->setObjectName(QString::fromUtf8("action_Reset"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/BrainViewer/Resources/cancel_128px_1209038_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_Reset->setIcon(icon10);
        action_Zoom = new QAction(BrainViewerClass);
        action_Zoom->setObjectName(QString::fromUtf8("action_Zoom"));
        action_Zoom->setCheckable(true);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/BrainViewer/Resources/zoom_in_128px_1200197_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_Zoom->setIcon(icon11);
        action_GrayLevel = new QAction(BrainViewerClass);
        action_GrayLevel->setObjectName(QString::fromUtf8("action_GrayLevel"));
        action_GrayLevel->setCheckable(true);
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/BrainViewer/Resources/brightness_128px_1193620_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_GrayLevel->setIcon(icon12);
        action_Move = new QAction(BrainViewerClass);
        action_Move->setObjectName(QString::fromUtf8("action_Move"));
        action_Move->setCheckable(true);
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/BrainViewer/Resources/move_Hand_128px_1154031_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_Move->setIcon(icon13);
        action_SwitchOfProperty = new QAction(BrainViewerClass);
        action_SwitchOfProperty->setObjectName(QString::fromUtf8("action_SwitchOfProperty"));
        action_SwitchOfProperty->setCheckable(true);
        action_Play = new QAction(BrainViewerClass);
        action_Play->setObjectName(QString::fromUtf8("action_Play"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/BrainViewer/Resources/play_128px_1197036_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_Play->setIcon(icon14);
        action_Stop = new QAction(BrainViewerClass);
        action_Stop->setObjectName(QString::fromUtf8("action_Stop"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/BrainViewer/Resources/stop_128px_1197040_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_Stop->setIcon(icon15);
        action_TestEntrance_01 = new QAction(BrainViewerClass);
        action_TestEntrance_01->setObjectName(QString::fromUtf8("action_TestEntrance_01"));
        action_TestEntrance_02 = new QAction(BrainViewerClass);
        action_TestEntrance_02->setObjectName(QString::fromUtf8("action_TestEntrance_02"));
        action_OpenDicomDirFile = new QAction(BrainViewerClass);
        action_OpenDicomDirFile->setObjectName(QString::fromUtf8("action_OpenDicomDirFile"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/BrainViewer/Resources/file_128px_1197084_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_OpenDicomDirFile->setIcon(icon16);
        action_OpenDicomFile = new QAction(BrainViewerClass);
        action_OpenDicomFile->setObjectName(QString::fromUtf8("action_OpenDicomFile"));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/BrainViewer/Resources/X_Ray_Hand_128px_1124752_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_OpenDicomFile->setIcon(icon17);
        action_PreviousPatient = new QAction(BrainViewerClass);
        action_PreviousPatient->setObjectName(QString::fromUtf8("action_PreviousPatient"));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/BrainViewer/Resources/hand_pointing_left_128px_1143134_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_PreviousPatient->setIcon(icon18);
        action_LatterPatient = new QAction(BrainViewerClass);
        action_LatterPatient->setObjectName(QString::fromUtf8("action_LatterPatient"));
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/BrainViewer/Resources/hand_pointing_right_128px_1143133_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_LatterPatient->setIcon(icon19);
        action_WindowWL_Default = new QAction(BrainViewerClass);
        action_WindowWL_Default->setObjectName(QString::fromUtf8("action_WindowWL_Default"));
        action_WindowWL_Default->setCheckable(true);
        action_WindowWL_All = new QAction(BrainViewerClass);
        action_WindowWL_All->setObjectName(QString::fromUtf8("action_WindowWL_All"));
        action_WindowWL_All->setCheckable(true);
        action_WindowWL_CT_Abdomen = new QAction(BrainViewerClass);
        action_WindowWL_CT_Abdomen->setObjectName(QString::fromUtf8("action_WindowWL_CT_Abdomen"));
        action_WindowWL_CT_Abdomen->setCheckable(true);
        action_WindowWL_CT_BloodVessel = new QAction(BrainViewerClass);
        action_WindowWL_CT_BloodVessel->setObjectName(QString::fromUtf8("action_WindowWL_CT_BloodVessel"));
        action_WindowWL_CT_BloodVessel->setCheckable(true);
        action_WindowWL_CT_Bones = new QAction(BrainViewerClass);
        action_WindowWL_CT_Bones->setObjectName(QString::fromUtf8("action_WindowWL_CT_Bones"));
        action_WindowWL_CT_Bones->setCheckable(true);
        action_WindowWL_CT_Brain = new QAction(BrainViewerClass);
        action_WindowWL_CT_Brain->setObjectName(QString::fromUtf8("action_WindowWL_CT_Brain"));
        action_WindowWL_CT_Brain->setCheckable(true);
        action_WindowWL_CT_Medias = new QAction(BrainViewerClass);
        action_WindowWL_CT_Medias->setObjectName(QString::fromUtf8("action_WindowWL_CT_Medias"));
        action_WindowWL_CT_Medias->setCheckable(true);
        action_WindowWL_CT_Lungs = new QAction(BrainViewerClass);
        action_WindowWL_CT_Lungs->setObjectName(QString::fromUtf8("action_WindowWL_CT_Lungs"));
        action_WindowWL_CT_Lungs->setCheckable(true);
        action_Registration = new QAction(BrainViewerClass);
        action_Registration->setObjectName(QString::fromUtf8("action_Registration"));
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/BrainViewer/Resources/aim_128px_1207156_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_Registration->setIcon(icon20);
        centralWidget = new QWidget(BrainViewerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        qvtkWidget = new QVTKWidget(centralWidget);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));
        sizePolicy.setHeightForWidth(qvtkWidget->sizePolicy().hasHeightForWidth());
        qvtkWidget->setSizePolicy(sizePolicy);
        qvtkWidget->setSizeIncrement(QSize(0, 0));
        qvtkWidget->setBaseSize(QSize(0, 0));
        qvtkWidget->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));

        gridLayout->addWidget(qvtkWidget, 0, 0, 1, 1);

        SliceScrollBar = new QScrollBar(centralWidget);
        SliceScrollBar->setObjectName(QString::fromUtf8("SliceScrollBar"));
        SliceScrollBar->setOrientation(Qt::Orientation::Vertical);

        gridLayout->addWidget(SliceScrollBar, 0, 1, 1, 1);

        BrainViewerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BrainViewerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1200, 17));
        menuBar->setAutoFillBackground(false);
        menuBar->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        menuBar->setNativeMenuBar(true);
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu->setAutoFillBackground(false);
        menu->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        menu_4->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        menu_5 = new QMenu(menuBar);
        menu_5->setObjectName(QString::fromUtf8("menu_5"));
        menu_5->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        menu_WindowSizeLevel = new QMenu(menuBar);
        menu_WindowSizeLevel->setObjectName(QString::fromUtf8("menu_WindowSizeLevel"));
        menu_WindowSizeLevel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        BrainViewerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BrainViewerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setAutoFillBackground(false);
        mainToolBar->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        BrainViewerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BrainViewerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        BrainViewerClass->setStatusBar(statusBar);
        dockWidget_Dir = new QDockWidget(BrainViewerClass);
        dockWidget_Dir->setObjectName(QString::fromUtf8("dockWidget_Dir"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        horizontalLayout = new QHBoxLayout(dockWidgetContents);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        treeView = new QTreeView(dockWidgetContents);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);

        horizontalLayout->addWidget(treeView);

        dockWidget_Dir->setWidget(dockWidgetContents);
        BrainViewerClass->addDockWidget(Qt::LeftDockWidgetArea, dockWidget_Dir);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_WindowSizeLevel->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menuBar->addAction(menu_5->menuAction());
        menu->addAction(action_OpenSeriesFolder);
        menu->addAction(action_OpenDicomDirFile);
        menu->addAction(action_OpenDicomFile);
        menu->addSeparator();
        menu->addAction(action_PreviousPatient);
        menu->addAction(action_LatterPatient);
        menu_2->addAction(action_back);
        menu_2->addAction(action_next);
        menu_3->addAction(action_Pointer);
        menu_3->addAction(action_Protractor);
        menu_3->addAction(action_Ruler);
        menu_3->addAction(action_Contour);
        menu_3->addAction(action_BiDimensional);
        menu_3->addAction(action_Reset);
        menu_3->addAction(action_Zoom);
        menu_3->addAction(action_GrayLevel);
        menu_3->addAction(action_Move);
        menu_3->addAction(action_Play);
        menu_3->addAction(action_Stop);
        menu_3->addSeparator();
        menu_3->addAction(action_Registration);
        menu_4->addAction(action_SwitchOfProperty);
        menu_5->addAction(action_TestEntrance_01);
        menu_5->addAction(action_TestEntrance_02);
        menu_WindowSizeLevel->addAction(action_WindowWL_Default);
        menu_WindowSizeLevel->addAction(action_WindowWL_All);
        menu_WindowSizeLevel->addSeparator();
        menu_WindowSizeLevel->addAction(action_WindowWL_CT_Abdomen);
        menu_WindowSizeLevel->addAction(action_WindowWL_CT_BloodVessel);
        menu_WindowSizeLevel->addAction(action_WindowWL_CT_Bones);
        menu_WindowSizeLevel->addAction(action_WindowWL_CT_Brain);
        menu_WindowSizeLevel->addAction(action_WindowWL_CT_Medias);
        menu_WindowSizeLevel->addAction(action_WindowWL_CT_Lungs);
        menu_WindowSizeLevel->addSeparator();
        menu_WindowSizeLevel->addAction(action_Negative);
        mainToolBar->addAction(action_OpenDicomDirFile);
        mainToolBar->addAction(action_OpenDicomFile);
        mainToolBar->addAction(action_OpenSeriesFolder);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_PreviousPatient);
        mainToolBar->addAction(action_LatterPatient);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_back);
        mainToolBar->addAction(action_Play);
        mainToolBar->addAction(action_next);
        mainToolBar->addAction(action_Stop);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_Pointer);
        mainToolBar->addAction(action_Zoom);
        mainToolBar->addAction(action_GrayLevel);
        mainToolBar->addAction(action_Move);
        mainToolBar->addAction(action_Protractor);
        mainToolBar->addAction(action_Ruler);
        mainToolBar->addAction(action_Contour);
        mainToolBar->addAction(action_BiDimensional);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_Negative);
        mainToolBar->addAction(action_Reset);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_Registration);

        retranslateUi(BrainViewerClass);
        QObject::connect(action_back, SIGNAL(triggered()), BrainViewerClass, SLOT(OnBackward()));
        QObject::connect(action_next, SIGNAL(triggered()), BrainViewerClass, SLOT(OnForward()));
        QObject::connect(action_Pointer, SIGNAL(triggered()), BrainViewerClass, SLOT(OnSelectedPointer()));
        QObject::connect(action_Protractor, SIGNAL(triggered()), BrainViewerClass, SLOT(OnSelectedProtractor()));
        QObject::connect(action_Ruler, SIGNAL(triggered()), BrainViewerClass, SLOT(OnSelectedRuler()));
        QObject::connect(action_Contour, SIGNAL(triggered()), BrainViewerClass, SLOT(OnSelectedContour()));
        QObject::connect(action_BiDimensional, SIGNAL(triggered()), BrainViewerClass, SLOT(OnSelectedBiDimensional()));
        QObject::connect(action_Negative, SIGNAL(triggered()), BrainViewerClass, SLOT(OnNegative()));
        QObject::connect(action_Reset, SIGNAL(triggered()), BrainViewerClass, SLOT(OnReset()));
        QObject::connect(action_GrayLevel, SIGNAL(triggered()), BrainViewerClass, SLOT(OnSelectedGrayLevel()));
        QObject::connect(action_Zoom, SIGNAL(triggered()), BrainViewerClass, SLOT(OnSelectedZoom()));
        QObject::connect(action_Move, SIGNAL(triggered()), BrainViewerClass, SLOT(OnSelectedMove()));
        QObject::connect(action_SwitchOfProperty, SIGNAL(triggered()), BrainViewerClass, SLOT(OnSwitchProperty()));
        QObject::connect(action_Play, SIGNAL(triggered()), BrainViewerClass, SLOT(OnPlay()));
        QObject::connect(action_Stop, SIGNAL(triggered()), BrainViewerClass, SLOT(OnStop()));
        QObject::connect(action_TestEntrance_01, SIGNAL(triggered()), BrainViewerClass, SLOT(OnTestEntrance_01()));
        QObject::connect(action_TestEntrance_02, SIGNAL(triggered()), BrainViewerClass, SLOT(OnTestEntrance_02()));
        QObject::connect(action_OpenDicomDirFile, SIGNAL(triggered()), BrainViewerClass, SLOT(OnOpenDicomDirFile()));
        QObject::connect(action_OpenSeriesFolder, SIGNAL(triggered()), BrainViewerClass, SLOT(OnOpenSeriesFolder()));
        QObject::connect(action_OpenDicomFile, SIGNAL(triggered()), BrainViewerClass, SLOT(OnOpenDicomFile()));
        QObject::connect(treeView, SIGNAL(customContextMenuRequested(QPoint)), BrainViewerClass, SLOT(on_treeView_customContextMenuRequested(QPoint)));
        QObject::connect(SliceScrollBar, SIGNAL(valueChanged(int)), BrainViewerClass, SLOT(OnSliceScrollBarValueChange(int)));
        QObject::connect(action_PreviousPatient, SIGNAL(triggered()), BrainViewerClass, SLOT(OnPreviousPatient()));
        QObject::connect(action_LatterPatient, SIGNAL(triggered()), BrainViewerClass, SLOT(OnLatterPatient()));
        QObject::connect(action_WindowWL_All, SIGNAL(triggered()), BrainViewerClass, SLOT(OnWindowWL_All()));
        QObject::connect(action_WindowWL_CT_Abdomen, SIGNAL(triggered()), BrainViewerClass, SLOT(OnWindowWL_CT_Abdomen()));
        QObject::connect(action_WindowWL_CT_BloodVessel, SIGNAL(triggered()), BrainViewerClass, SLOT(OnWindowWL_CT_BloodVessel()));
        QObject::connect(action_WindowWL_CT_Bones, SIGNAL(triggered()), BrainViewerClass, SLOT(OnWindowWL_CT_Bones()));
        QObject::connect(action_WindowWL_CT_Brain, SIGNAL(triggered()), BrainViewerClass, SLOT(OnWindowWL_CT_Brain()));
        QObject::connect(action_WindowWL_CT_Medias, SIGNAL(triggered()), BrainViewerClass, SLOT(OnWindowWL_CT_Medias()));
        QObject::connect(action_WindowWL_CT_Lungs, SIGNAL(triggered()), BrainViewerClass, SLOT(OnWindowWL_CT_Lungs()));
        QObject::connect(action_WindowWL_Default, SIGNAL(triggered()), BrainViewerClass, SLOT(OnWindowWL_Defaut()));
        QObject::connect(action_Registration, SIGNAL(triggered()), BrainViewerClass, SLOT(OnRegistration()));

        QMetaObject::connectSlotsByName(BrainViewerClass);
    } // setupUi

    void retranslateUi(QMainWindow *BrainViewerClass)
    {
        BrainViewerClass->setWindowTitle(QCoreApplication::translate("BrainViewerClass", "BrainSight", nullptr));
        action_OpenSeriesFolder->setText(QCoreApplication::translate("BrainViewerClass", "\346\211\223\345\274\200Series\347\233\256\345\275\225", nullptr));
        action_back->setText(QCoreApplication::translate("BrainViewerClass", "\344\270\212\344\270\200\345\274\240", nullptr));
        action_next->setText(QCoreApplication::translate("BrainViewerClass", "\344\270\213\344\270\200\345\274\240", nullptr));
        action_Pointer->setText(QCoreApplication::translate("BrainViewerClass", "\346\227\240", nullptr));
        action_Protractor->setText(QCoreApplication::translate("BrainViewerClass", "\351\207\217\350\247\222\345\231\250", nullptr));
        action_Ruler->setText(QCoreApplication::translate("BrainViewerClass", "\346\265\213\350\267\235\345\260\272", nullptr));
        action_Contour->setText(QCoreApplication::translate("BrainViewerClass", "\350\275\256\345\273\223", nullptr));
#if QT_CONFIG(tooltip)
        action_Contour->setToolTip(QCoreApplication::translate("BrainViewerClass", "\350\275\256\345\273\223", nullptr));
#endif // QT_CONFIG(tooltip)
        action_BiDimensional->setText(QCoreApplication::translate("BrainViewerClass", "\344\272\214\347\273\264\346\240\207\345\260\272", nullptr));
        action_Negative->setText(QCoreApplication::translate("BrainViewerClass", "\350\264\237\347\211\207", nullptr));
        action_Reset->setText(QCoreApplication::translate("BrainViewerClass", "\345\244\215\344\275\215", nullptr));
        action_Zoom->setText(QCoreApplication::translate("BrainViewerClass", "\347\274\251\346\224\276", nullptr));
        action_GrayLevel->setText(QCoreApplication::translate("BrainViewerClass", "\347\201\260\351\230\266", nullptr));
#if QT_CONFIG(tooltip)
        action_GrayLevel->setToolTip(QCoreApplication::translate("BrainViewerClass", "\347\201\260\351\230\266", nullptr));
#endif // QT_CONFIG(tooltip)
        action_Move->setText(QCoreApplication::translate("BrainViewerClass", "\347\247\273\345\212\250", nullptr));
        action_SwitchOfProperty->setText(QCoreApplication::translate("BrainViewerClass", "\345\261\236\346\200\247", nullptr));
        action_Play->setText(QCoreApplication::translate("BrainViewerClass", "\346\222\255\346\224\276", nullptr));
        action_Stop->setText(QCoreApplication::translate("BrainViewerClass", "\345\201\234\346\255\242", nullptr));
        action_TestEntrance_01->setText(QCoreApplication::translate("BrainViewerClass", "\346\265\213\350\257\225\345\205\245\345\217\2431", nullptr));
        action_TestEntrance_02->setText(QCoreApplication::translate("BrainViewerClass", "\346\265\213\350\257\225\345\205\245\345\217\2432", nullptr));
        action_OpenDicomDirFile->setText(QCoreApplication::translate("BrainViewerClass", "\346\211\223\345\274\200DICOMDIR\346\226\207\344\273\266", nullptr));
        action_OpenDicomFile->setText(QCoreApplication::translate("BrainViewerClass", "\346\211\223\345\274\200Dicom\346\226\207\344\273\266", nullptr));
        action_PreviousPatient->setText(QCoreApplication::translate("BrainViewerClass", "\344\270\212\344\270\200\344\270\252\347\227\205\344\272\272", nullptr));
        action_LatterPatient->setText(QCoreApplication::translate("BrainViewerClass", "\344\270\213\344\270\200\344\270\252\347\227\205\344\272\272", nullptr));
        action_WindowWL_Default->setText(QCoreApplication::translate("BrainViewerClass", "\351\273\230\350\256\244", nullptr));
        action_WindowWL_All->setText(QCoreApplication::translate("BrainViewerClass", "\345\205\250\351\203\250\345\212\250\346\200\201\350\214\203\345\233\264", nullptr));
        action_WindowWL_CT_Abdomen->setText(QCoreApplication::translate("BrainViewerClass", "CT-\350\205\271", nullptr));
        action_WindowWL_CT_BloodVessel->setText(QCoreApplication::translate("BrainViewerClass", "CT-\350\241\200\347\256\241", nullptr));
        action_WindowWL_CT_Bones->setText(QCoreApplication::translate("BrainViewerClass", "CT-\351\252\250\351\252\274", nullptr));
        action_WindowWL_CT_Brain->setText(QCoreApplication::translate("BrainViewerClass", "CT-\350\204\221", nullptr));
        action_WindowWL_CT_Medias->setText(QCoreApplication::translate("BrainViewerClass", "CT-\347\272\265\350\206\210", nullptr));
        action_WindowWL_CT_Lungs->setText(QCoreApplication::translate("BrainViewerClass", "CT-\350\202\272", nullptr));
        action_Registration->setText(QCoreApplication::translate("BrainViewerClass", "\351\205\215\345\207\206\345\267\245\345\205\267", nullptr));
        menu->setTitle(QCoreApplication::translate("BrainViewerClass", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("BrainViewerClass", "\344\277\241\346\201\257", nullptr));
        menu_3->setTitle(QCoreApplication::translate("BrainViewerClass", "\345\267\245\345\205\267", nullptr));
        menu_4->setTitle(QCoreApplication::translate("BrainViewerClass", "\347\252\227\345\217\243", nullptr));
        menu_5->setTitle(QCoreApplication::translate("BrainViewerClass", "\346\265\213\350\257\225", nullptr));
        menu_WindowSizeLevel->setTitle(QCoreApplication::translate("BrainViewerClass", "\347\252\227\345\256\275\347\252\227\344\275\215", nullptr));
#if QT_CONFIG(tooltip)
        dockWidget_Dir->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        dockWidget_Dir->setWindowTitle(QCoreApplication::translate("BrainViewerClass", "DICOMDIR", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BrainViewerClass: public Ui_BrainViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BRAINVIEWER_H
