#ifndef __CUSTOMWIDGET_H__
#define __CUSTOMWIDGET_H__

#include <QWidget>
#include <QDialog>
#include <QMutex>
#include <QTimer>
#include <QLineEdit>
#include <QPushButton>
#include <QMouseEvent>
#include <QShowEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QStyleOption>
#include <QPainter>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>

#include "myapp.h"


QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
class QLineEdit;
class QHBoxLayout;
class QVBoxLayout;
QT_END_NAMESPACE

class CustomWidget : public QWidget{
    Q_OBJECT

public:
    explicit CustomWidget(QWidget* parent = 0);

signals:

protected:
    void paintEvent(QPaintEvent *event) override;
};

class CustomMoveWidget : public CustomWidget{
    Q_OBJECT

public:
    explicit CustomMoveWidget(QWidget* parent = 0);
    ~CustomMoveWidget();

protected:
    QPoint mousePoint;
    bool m_mousePressed;

    void mouseMoveEvent(QMouseEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;
};

class CustomDialog : public QDialog{
    Q_OBJECT

public:
    explicit CustomDialog(QWidget* parent = 0);
    ~CustomDialog();

protected:
    QPoint mousePoint;
    bool m_mousePressed;
    QSize m_nNormalSize;

    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
};

class CBaseDialog : public CustomDialog{
    Q_OBJECT
public:
    explicit CBaseDialog(QWidget* parent = 0);
    ~CBaseDialog();

    void SetWinIcon(QPixmap pixmap);
    void SetWinTitle(const QString& text);

private:
    QWidget* winTitle_widget;
    QLabel* winIcon_label;
    QLabel* winTitle_label;
    QPushButton* winMin_btn;
    QPushButton* winclose_btn;

protected:
    QWidget* body_widget;
};

class CMessageBox : public CBaseDialog{
    Q_OBJECT

public:
    typedef enum{
        E_Information = 0x01,
        E_warning,
        E_Question,
        E_MSGTYPE_Error
    } E_MSGTYPE;

public:
    explicit CMessageBox(QWidget* parent = 0);
    ~CMessageBox();

    //显示消息
    void showMessage(const QString* content, const quint8& msgType = CMessageBox::E_Information, const QString& title = "");

    void startTimer();

    static int information(QWidget* parent, const QString& content, const QString& title = "提示");
    static int question(QWidget* parent, const QString& content, const QString& title = "询问");
    static int warnig(QWidget* parent, const QString& content, const QString& title = "告警");

private:
    QLabel* icon_label;
    QLabel* msgContent_label;

    QPushButton* ok_btn;
    QPushButton* cancel_btn;

    QTimer* m_timer;
    int m_nTimerCount;

public slots:
    void timeout_slot();

};

class CInputDialog : public CBaseDialog{
    Q_OBJECT

public:
    explicit CInputDialog(QWidget* parent = 0);
    ~CInputDialog();

    static QString getInputText(QWidget* parent, const QString& text = "",
                                const QString& title = "输入", QLineEdit::EchoMode mode = QLineEdit::Normal);

    QString getText() const;
    void setInputText(const QString& text);
    void setEchoMode(QLineEdit::EchoMode mode);

private:
    static CInputDialog* self;
    QLineEdit* text_label;

    QPushButton* ok_btn;
    QPushButton* cancel_btn;
};

#endif
