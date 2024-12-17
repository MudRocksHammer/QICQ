#include "ConversationCell.h"

ConversationCell::ConversationCell(QWidget *parent) : QWidget(parent)
{
    initUI();
    QFile file(":/resource/qss/ContactWindow/conversationList.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(file.readAll());
    file.close();
}

void ConversationCell::setData(QVector<Cell> &cell)
{
    m_model->setData(cell);
}

void ConversationCell::addData(const Cell &cell)
{
    m_model->addData(cell);
}

void ConversationCell::initUI()
{
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);

    m_listview = new QListView(this);
    m_model = new QQCellModel(this);
    m_delegate = new QQCellDelegate(this);

    m_listview->setItemDelegate(m_delegate);
    m_listview->setModel(m_model);

    vlayout->addWidget(m_listview);

    this->setLayout(vlayout);
}
