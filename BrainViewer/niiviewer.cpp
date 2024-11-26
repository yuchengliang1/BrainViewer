#include "niiviewer.h"
#include "ui_niiviewer.h"

NiiViewer::NiiViewer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NiiViewer)
{
    ui->setupUi(this);
}

NiiViewer::~NiiViewer()
{
    delete ui;
}
