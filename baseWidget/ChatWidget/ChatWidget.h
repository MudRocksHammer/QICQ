#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QFile>

#include "MessageList.h"
#include "ChatTitle.h"
#include "ChatInput.h"
#include "customwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class ChatWidget;
}
QT_END_NAMESPACE

class ChatWidget : public CustomMoveWidget
{
    Q_OBJECT
public:
    ChatWidget(QWidget *parent = 0);

    void setData(QVector<ItemInfo> &infos);
    void scrollToBottom();

private:
    void initUI();

private:
    void close_btn_clicked();

private:
    MessageList *m_messageList;
    ChatTitle *m_title;
    ChatInput *m_input;
    Ui::ChatWidget *ui;
};
