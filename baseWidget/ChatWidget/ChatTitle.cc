#include "ChatTitle.h"
#include "ui_chattitle.h"

ChatTitle::ChatTitle(QWidget *parent) : QWidget(parent), ui(new Ui::ChatTitle)
{
    ui->setupUi(this);
    initUI();
}

ChatTitle::~ChatTitle()
{
    delete ui;
}

void ChatTitle::setPartnerName(const QString &name)
{
}

void ChatTitle::paintEvent(QPaintEvent *e)
{
}

void ChatTitle::initUI()
{
    QFile file(":/resource/qss/ChatWindow/chatTitle.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(file.readAll());
    file.close();
}

void ChatTitle::nameBtn_clicked_slot()
{
}

void ChatTitle::dialAudioBtn_clicked_slot()
{
}

void ChatTitle::dialVideoBtn_clicked_slot()
{
}

void ChatTitle::moreBtn_clicked_slot()
{
}
