#include "customwidget.h"

CustomMoveWidget::CustomMoveWidget(QWidget *parent) : m_mousePressed(false)
{

}

CustomMoveWidget::~CustomMoveWidget()
{

}

void CustomMoveWidget::mouseMoveEvent(QMouseEvent *e)
{
     if(m_mousePressed){
        QPoint movePoint = e->globalPos() - mousePoint;
        move(movePoint);
    }
}

void CustomMoveWidget::mousePressEvent(QMouseEvent *e)
{
    m_mousePressed = true;
    mousePoint = e->pos();
}

void CustomMoveWidget::mouseReleaseEvent(QMouseEvent *e)
{
    m_mousePressed = false;
    
}

CustomWidget::CustomWidget(QWidget *parent)
{

}

void CustomWidget::paintEvent(QPaintEvent *event)
{

}

CustomDialog::CustomDialog(QWidget *parent)
{

}

CustomDialog::~CustomDialog()
{

}

void CustomDialog::mousePressEvent(QMouseEvent *e)
{

}

void CustomDialog::mouseMoveEvent(QMouseEvent *e)
{

}

void CustomDialog::mouseReleaseEvent(QMouseEvent *e)
{

}

CBaseDialog::CBaseDialog(QWidget *parent)
{

}

CBaseDialog::~CBaseDialog()
{

}

void CBaseDialog::SetWinIcon(QPixmap pixmap)
{

}

void CBaseDialog::SetWinTitle(const QString &text)
{

}

CMessageBox::CMessageBox(QWidget *parent)
{

}

CMessageBox::~CMessageBox()
{

}

void CMessageBox::showMessage(const QString *content, const quint8 &msgType, const QString &title)
{

}

void CMessageBox::startTimer()
{

}

int CMessageBox::information(QWidget *parent, const QString &content, const QString &title)
{
    return 0;
}

int CMessageBox::question(QWidget *parent, const QString &content, const QString &title)
{
    return 0;
}

int CMessageBox::warnig(QWidget *parent, const QString &content, const QString &title)
{
    return 0;
}

void CMessageBox::timeout_slot()
{

}

CInputDialog::CInputDialog(QWidget *parent)
{

}

CInputDialog::~CInputDialog()
{

}

QString CInputDialog::getInputText(QWidget *parent, const QString &text, const QString &title, QLineEdit::EchoMode mode)
{
    return "";
}

QString CInputDialog::getText() const
{
    return "";
}

void CInputDialog::setInputText(const QString &text)
{

}

void CInputDialog::setEchoMode(QLineEdit::EchoMode mode)
{

}
