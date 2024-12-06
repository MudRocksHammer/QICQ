#include "cutdialog.h"

CutDialog::CutDialog(QWidget* parent) : QFrame(parent)
{
    setWindowFlag(Qt::FramelessWindowHint);

    m_left = false;
    m_right = false;
    m_top = false;
    m_bottom = false;
    m_isMoving = false;
    m_mouseDown = false;

    setMouseTracking(true);
    setGeometry(0, 0, 150, 150);

    m_label = new QLabel(this);

    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(m_label);
    layout->setMargin(0);
    setLayout(layout);
    m_label->setMouseTracking(true);
}

CutDialog::~CutDialog(){

}

void CutDialog::resizeEvent(QResizeEvent *e){

}

void CutDialog::mousePressEvent(QMouseEvent *e){
    m_startPoint = e->pos();
    m_mouseDown = e->button() == Qt::LeftButton;
}

void CutDialog::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPen pen;
    QVector<qreal> dashes;
    qreal space = 3;
    dashes << 5 << space << 5 << space;
    pen.setDashPattern(dashes);
    pen.setColor(Qt::white);

    QPen pen0;
    pen0.setColor(QColor(54, 158, 254, 120));
    pen0.setWidth(2);
    painter.setPen(pen0);
    painter.drawRect(1, 0, width()-2, width()-2);

    painter.setPen(pen);
    int x_pos = (int)width() /3;
    int y_pos = (int)height() /3.0;
    painter.drawLine(x_pos, 0, x_pos, height());
    painter.drawLine(2*x_pos, 0, 2*x_pos, height());
    painter.drawLine(0, y_pos, width(), y_pos);
    painter.drawLine(0, 2*y_pos, width(), 2*y_pos);
    painter.drawEllipse(0, 0, width(), width());
}

QRect CutDialog::getResizeGem(QRect oldGeo, QPoint mousePoint){
    QRect g = oldGeo;
    bool lorr = m_left | m_right;
    bool torb = m_top | m_bottom;
    int dx = mousePoint.x() - m_startPoint.x();
    int dy = mousePoint.y() - m_startPoint.y();
    if(lorr && torb){
        int maxLen = qMin(qAbs(dx), qAbs(dy));
        if(m_left && m_top && dx*dy > 0){
            g.setLeft(dx > 0?g.left() + maxLen : g.left() - maxLen);
            g.setTop(dy > 0?g.top() + maxLen : g.top() - maxLen);
        }
        if(m_right && m_top && dx*dy < 0){
            g.setRight(dx > 0?g.left() + maxLen : g.right() - maxLen);
            g.setTop(dy > 0?g.top() + maxLen : g.top() - maxLen);
        }
        if(m_right && m_bottom && dx*dy > 0)
        {
            g.setRight(dx>0 ? g.right() + maxLen:g.right() - maxLen);
            g.setBottom(dy >0? g.bottom() + maxLen : g.bottom() - maxLen);
        }
        if(m_left && m_bottom && dx*dy < 0)
        {
            g.setLeft(dx >0 ?g.left() + maxLen : g.left() - maxLen);
            g.setBottom(dy >0? g.bottom() + maxLen : g.bottom() - maxLen);
        }
        return g;
    }
    else if(lorr){
        if(m_left)
            g.setLeft(g.left() + dx);
        if(m_right)
            g.setRight(g.right() + dx);
        int len = g.width() - oldGeo.width();
        int intHeight = (int)len/2;

        g.setTop(g.top() - intHeight);
        g.setBottom(g.bottom() + len - intHeight);
    }
    else if(torb){
        if(m_bottom)
            g.setBottom(g.bottom() + dy);
        if(m_top)
            g.setTop(g.top() - oldGeo.height());
        int height = g.height() - oldGeo.height();
        int intWidth = (int)height/2;

        g.setLeft(g.left() - intWidth);
        g.setRight(g.right() + height - intWidth);
    }
    return g;
}

void CutDialog::mouseMoveEvent(QMouseEvent *e){
    QPoint dragPoint = e->pos();
    int x = e->x();
    int y = e->y();

    if(m_mouseDown){
        QRect newRect = getResizeGem(geometry(), dragPoint);
        if(parentWidget()->rect().contains(newRect))
            setGeometry(newRect);
        m_startPoint = QPoint(!m_right?m_startPoint.x():e->x()
                                       , !m_bottom?m_startPoint.y():e->y());
        if(!m_left && !m_right && !m_bottom && !m_top)
        {
            QPoint p = QPoint((pos().x()+dragPoint.x() - m_startPoint.x()),
                              (pos().y()+dragPoint.y() - m_startPoint.y()));
            QPoint dragEndge = p;
            dragEndge.setX(dragEndge.x() + rect().width());
            dragEndge.setY(dragEndge.y() + rect().height());
            p.setX(p.x() < 0 ? 0 : p.x());
            p.setX(dragEndge.x() > parentWidget()->width() ?
                       parentWidget()->width()-rect().width():
                       p.x());

            p.setY(p.y() < 0 ? 0 : p.y());
            p.setY(dragEndge.y() > parentWidget()->height() ?
                       parentWidget()->height()-rect().height() :
                       p.y());
            move(p);
        }
        else {

        }
    }
    else{
        QRect r = rect();
        m_left = qAbs(x - r.left())  < 5;
        m_right = qAbs(x - r.right()) < 5;
        m_bottom = qAbs(y - r.bottom()) < 5;
        m_top = qAbs(y - r.top()) < 5;
        bool lorr = m_left | m_right;
        bool torb = m_top | m_bottom;
        if(lorr && torb)
        {
            if((m_left && m_top) || (m_right && m_bottom))
            {
                setCursor(Qt::SizeFDiagCursor);
            }
            else
                setCursor(Qt::SizeBDiagCursor);
        }
        else if(lorr)
            setCursor(Qt::SizeHorCursor);
        else if(torb)
            setCursor(Qt::SizeVerCursor);
        else
        {
            setCursor(Qt::SizeAllCursor);
            m_bottom = m_left = m_right = m_top = false;
        }
    }
}

void CutDialog::mouseReleaseEvent(QMouseEvent *e){
    m_mouseDown = false;
    Q_EMIT signalMoved();
}
