#include "QQCell.h"

QQCell::QQCell(QWidget *parent)
{
    initUI();
}

void QQCell::setData(QVector<Cell> &cell)
{
    m_model->setData(cell);
}

void QQCell::addData(const Cell &cell)
{
    m_model->addData(cell);
}

void QQCell::initUI()
{
    QFile file(":/resource/qss/cellList.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(file.readAll());

    QVBoxLayout *vlayout = new QVBoxLayout(this);

    m_listView = new QListView(this);
    m_model = new QQCellModel(this);
    m_delegate = new QQCellDelegate(this);
    m_title = new QQCellTitle(this);

    m_listView->setModel(m_model);
    m_listView->setItemDelegate(m_delegate);

    vlayout->setMargin(0);
    vlayout->addWidget(m_title);
    vlayout->addWidget(m_listView);
    vlayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    m_listView->setVisible(false);

    this->setLayout(vlayout);

    connect(m_title, &QQCellTitle::titleClicked_signal, this, &QQCell::titleClicked_slot);
}

void QQCell::titleClicked_slot(bool open)
{
    m_listView->setVisible(open);
}