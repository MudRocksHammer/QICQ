#include "ChatWidget.h"
#include "ui_chatwidget.h"

ChatWidget::ChatWidget(QWidget *parent) : CustomMoveWidget(parent), ui(new Ui::ChatWidget)
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

void ChatWidget::hideTitle()
{
    ui->widget->hide();
}

void ChatWidget::showTitle()
{
    ui->widget->show();
}

bool ChatWidget::eventFilter(QObject *obj, QEvent *e)
{

    return false;
}

void ChatWidget::initUI()
{
    this->setWindowFlag(Qt::FramelessWindowHint);

    m_messageList = new MessageList(this);
    m_title = new ChatTitle(this);
    m_input = new ChatInput(this);

    m_messageList->setObjectName("messageList");
    m_title->setObjectName("title");

    ui->verticalLayout->addWidget(m_title);
    ui->verticalLayout->addWidget(m_messageList);
    ui->verticalLayout->addWidget(m_input);

    connect(ui->close_btn, &QPushButton::clicked, this, &ChatWidget::close_btn_clicked);
}

void ChatWidget::close_btn_clicked()
{
    this->close();
}
