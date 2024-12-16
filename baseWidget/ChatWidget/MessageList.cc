#include "MessageList.h"

MessageList::MessageList(QWidget *parent) : QWidget(parent)
{
    initUI();
}

void MessageList::addText(const ItemInfo &text)
{
    m_model->addInfo(text);
}

void MessageList::addTexts(QVector<ItemInfo> &texts)
{
    m_model->addInfos(texts);
}

void MessageList::setMessage(QVector<ItemInfo> &mes)
{
    m_model->setInfo(mes);
}

void MessageList::scrollToBottom()
{
    m_listview->scrollToBottom();
}

void MessageList::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
}

void MessageList::initUI()
{

    QVBoxLayout *vlayout = new QVBoxLayout(this);

    m_delegate = new MessageDelegate(this);
    m_model = new MessageModel(this);
    m_listview = new QListView(this);

    m_listview->setModel(m_model);
    m_listview->setItemDelegate(m_delegate);
    m_listview->setObjectName("listView");

    vlayout->setMargin(0);
    vlayout->addWidget(m_listview);

    this->setLayout(vlayout);

    // TODO: manipulate bubble

    QFile file(":/resource/qss/ChatWindow/conv_list.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(file.readAll());
    file.close();
}
