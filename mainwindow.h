#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QFile>
#include <QDebug>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QWidget>
#include <QAction>
#include <QIcon>

#include "baseWidget/customwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public CustomMoveWidget
{
    Q_OBJECT
    enum class ResizeDirection{
        Left,
        Right,
        Top,
        Bottom,
        None
    };
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initUI();
    void initConnect();

protected:
    void enterEvent(QEvent* e) override;
    void leaveEvent(QEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;

private slots:
    void pushBtn_clicked();
    void pushBtn2_clicked();
    void pushBtn3_clicked();
    void stackedWidgetChanged(int);

    void trayIcon_clicked_slot(QSystemTrayIcon::ActivationReason);
    void trayMenu_clicked_slot(QAction *);

    void initSysTrayIcon();

    /// @brief check if mouse current position on the edge of widget
    /// @param  mouse position
    /// @return 
    bool onHorizontalEdge(QPoint);
    /// @brief vertical edge
    /// @param  mouse position
    /// @return 
    bool onVerticalEdge(QPoint);

private:
    Ui::MainWindow *ui;

    int s_index = 0;
    bool m_bQuit;
    /// @brief mouse event is pressed
    bool isPressing;
    QWidget* m_chatWidget;

    /// @brief moving properties member
    ResizeDirection m_direction;

    QSystemTrayIcon *m_trayIcon;
};

#endif // MAINWINDOW_H