#include "QQCellDelegate.h"

#include <QDebug>
#include <QEvent>

QQCellDelegate::QQCellDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
}

void QQCellDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    QString name = index.data(Cell::NameRole).toString();
    QString head = index.data(Cell::HeadRole).toString();
    QString state = index.data(Cell::StateRole).toString();
    QString staPic = index.data(Cell::StaPicRole).toString();
    QString lastTime = index.data(Cell::TimeStampRole).toString();
    QString ctrlPic = index.data(Cell::CtrlPicRole).toString();

    QRect rect = option.rect;
    if (option.state & QStyle::State_Selected)
        painter->fillRect(rect, QColor(45, 132, 230));

    // draw head picture
    QPixmap head_pic(head);
    int padding = (rect.height() - head_pic.height()) / 2;
    QRect headRect(rect.left() + padding, rect.top() + padding, head_pic.height(), head_pic.height());
    painter->drawPixmap(headRect, head_pic);

    int text_padding = (rect.height() - painter->fontMetrics().height() * 2) / 3;
    QFontMetrics metric(painter->font());
    // draw name using font rect
    QRect nameRect(headRect.right() + padding, rect.top() + text_padding, metric.horizontalAdvance(name), metric.height());
    painter->drawText(nameRect, name);

    // draw state
    QFont font = painter->font();
    font.setPixelSize(14);
    painter->setFont(font);
    painter->setPen(QPen(Qt::gray));
    QRect stateRect(headRect.right() + padding, nameRect.bottom() + text_padding, metric.horizontalAdvance(state), metric.height());
    painter->drawText(stateRect, state);

    // TODO: CtrlPic, statePic, lastTime display, text oversized display

    painter->restore();
}

QSize QQCellDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(200, 60);
}

bool QQCellDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonDblClick)
    {
        emit cellDoubleClicked_signal(index.data(Cell::NameRole).toString());
    }
    return false;
}
