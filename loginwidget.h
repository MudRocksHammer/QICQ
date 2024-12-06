#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QFile>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <functional>
#include "baseWidget/customwidget.h"

#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWidget; }
QT_END_NAMESPACE

class LoginWidget : public CustomMoveWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

    void initConnection();
    void initUI();

    // void mouseMoveEvent(QMouseEvent *event) override;
    // void mousePressEvent(QMouseEvent *event) override;
    // void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

protected:
    void keyPressEvent(QKeyEvent* e) override;

private slots:
    void on_loginBtnClicked();

signals:

private:
    Ui::LoginWidget* ui;
    bool bDaylight = false;
};

#endif // LOGINWIDGET_H
