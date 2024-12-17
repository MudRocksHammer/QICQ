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
#include <QDateTime>
#include <QButtonGroup>

#include "baseWidget/customwidget.h"
#include "baseWidget/QQCell/QQCell.h"
#include "baseWidget/ChatWidget/ChatWidget.h"
#include "baseWidget/QQCell/ConversationCell.h"
#include "comapi/unit.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public CustomMoveWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void enterEvent(QEvent *e) override;
    void leaveEvent(QEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

private:
    void initUI();
    void initConnect();
    void temporaryTest();

private slots:
    void conv_btn_clicked(bool);
    void contact_btn_clicked(bool);
    void btnGrp_toggled(QAbstractButton *btn, bool check);

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
    QWidget *m_chatWidget;

    /// @brief moving properties member
    Unit::ResizeDirection m_direction;

    QSystemTrayIcon *m_trayIcon;

    QVector<QQCell *> m_contact_cell;
    QVector<QQCell *> m_conversation_cell;
};

#endif // MAINWINDOW_H