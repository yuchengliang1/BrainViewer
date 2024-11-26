#ifndef NIIVIEWER_H
#define NIIVIEWER_H

#include <QWidget>

namespace Ui {
class NiiViewer;
}

class NiiViewer : public QWidget
{
    Q_OBJECT

public:
    explicit NiiViewer(QWidget *parent = nullptr);
    ~NiiViewer();

private:
    Ui::NiiViewer *ui;
};

#endif // NIIVIEWER_H
