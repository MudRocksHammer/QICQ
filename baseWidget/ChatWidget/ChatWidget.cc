#include "ChatWidget.h"
#include "ui_chatwidget.h"

ChatWidget::ChatWidget(QWidget *parent) : QWidget(parent), ui(new Ui::ChatWidget)
{
    ui->setupUi(this);
    initUI();

    QFile file(":/resource/qss/ChatWindow/chatWindow.qss");
    file.open(QFile::ReadOnly);
    this->setStyleSheet(file.readAll());
    file.close();
}

void ChatWidget::setData(QVector<ItemInfo> &infos)
{
    m_messageList->setMessage(infos);
}

void ChatWidget::scrollToBottom()
{
    m_messageList->scrollToBottom();
}

void ChatWidget::initUI()
{
    m_messageList = new MessageList(this);
    m_title = new ChatTitle(this);
    m_input = new ChatInput(this);

    m_messageList->setObjectName("messageList");
    m_title->setObjectName("title");

    ui->verticalLayout->addWidget(m_title);
    ui->verticalLayout->addWidget(m_messageList);
    ui->verticalLayout->addWidget(m_input);
}
