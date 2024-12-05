#pragma once
#include <QVTKWidget.h>
#include <qevent.h>

class QVTKWheelWidget : public QVTKWidget {
    Q_OBJECT
public:
    explicit QVTKWheelWidget(QWidget* parent = nullptr) : QVTKWidget(parent) {}

signals:
    void wheelScrolled(int delta);

protected:
    void wheelEvent(QWheelEvent* event) override {
        int delta = event->delta();
        emit wheelScrolled(delta); // 发出自定义信号
        event->accept();
    }
};