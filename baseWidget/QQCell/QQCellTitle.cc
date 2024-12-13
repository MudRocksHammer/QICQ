#include "QQCellTitle.h"

QQCellTitle::QQCellTitle(QWidget *parent) : QWidget(parent), m_online(0), m_total(0), m_isHover(false), m_isOpen(false)
{
    initUI();
    installEventFilter(this);
}

void QQCellTitle::setCount(const int &online, const int &total)
{
    m_online = online;
    m_total = total;
    updateUI();
}
void QQCellTitle::setName(const QString &name)
{
    m_name = name;
    updateUI();
}
void QQCellTitle::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    if (m_isHover)
        painter.fillRect(this->rect(), QColor(64, 64, 64));
}
bool QQCellTitle::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == this)
    {
        if (e->type() == QEvent::Enter)
        {
            m_isHover = true;
        }
        else if (e->type() == QEvent::Leave)
        {
            m_isHover = false;
        }
        else if (e->type() == QEvent::MouseButtonPress)
        {
            m_isOpen = !m_isOpen;
            emit titleClicked_signal(m_isOpen);
        }
        updateUI();
    }
    return false;
}
void QQCellTitle::initUI()
{
    QHBoxLayout *hlayout = new QHBoxLayout(this);

    m_arrow_label = new QLabel(this);
    m_name_label = new QLabel(this);
    m_count_label = new QLabel(this);

    m_arrow_label->setFixedWidth(20);

    hlayout->addWidget(m_arrow_label);
    hlayout->addWidget(m_name_label);
    hlayout->addWidget(m_count_label, 0, Qt::AlignRight);

    this->setLayout(hlayout);

    updateUI();
}

void QQCellTitle::updateUI()
{
    m_arrow_label->setPixmap(m_isOpen ? QPixmap(":/resource/common/arrow_down.png") : QPixmap(":/resource/common/arrow_right.png"));

    m_name_label->setText(m_name);

    m_count_label->setText("(" + QString::number(m_online) + "/" + QString::number(m_total) + ")");

    update();
}
