#include "ChatInput.h"
#include "ui_chatinput.h"

ChatInput::ChatInput(QWidget *parent) : QWidget(parent), ui(new Ui::ChatInput)
{
    ui->setupUi(this);
    initUI();
}

ChatInput::~ChatInput()
{
    delete ui;
}

void ChatInput::initUI()
{
    QFile file(":/resource/qss/ChatWindow/chatInput.qss");
    file.open(QFile::ReadOnly);
    this->setStyleSheet(file.readAll());
    file.close();
}

void ChatInput::emojiBtn_clicked_slot()
{
}

void ChatInput::cutScreenBtn_clicked_slot()
{
}

void ChatInput::fileBtn_clicked_slot()
{
}

void ChatInput::pictureBtn_clicked_slot()
{
}

void ChatInput::audioMsgBtn_clicked_slot()
{
}

void ChatInput::historyBtn_clicked_slot()
{
}

void ChatInput::sendBtn_clicked_slot()
{
}
