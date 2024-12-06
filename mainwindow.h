#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QFile>
#include <QDebug>

#include "baseWidget/customwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public CustomMoveWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initUI();
    void initConnect();

protected:
    // void mousePressEvent(QMouseEvent* e) override;
    // void mouseMoveEvent(QMouseEvent* e) override;
    // void mouseReleaseEvent(QMouseEvent* e) override;

private slots:
    void pushBtn_clicked();
    void pushBtn3_clicked();
    void stackedWidgetChanged(int);

private:
    Ui::MainWindow *ui;

    int s_index = 0;
};

#endif // MAINWINDOW_H