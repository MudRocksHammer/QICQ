#include "MessageDelegate.h"

#include <QDebug>

MessageDelegate::MessageDelegate(QObject *parent) : QStyledItemDelegate(parent), m_height(ITEM_HEIGHT), m_font_size(ITEM_FONT_SIZE)
{
}

void MessageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    QFont font = painter->font();
    QPen pen = painter->pen();

    // TODO:font size changeable, make a config read module
    QString userName = index.data(ItemInfo::UserNameRole).toString();
    QString headStr = index.data(ItemInfo::HeadRole).toString();
    QString message = index.data(ItemInfo::MessageRole).toString();
    QString dateStr = index.data(ItemInfo::DateTimeRole).toString();

    Unit::Orientation orientation = (Unit::Orientation)index.data(ItemInfo::OrientationRole).toInt();
    Unit::MessageType msgType = (Unit::MessageType)index.data(ItemInfo::MsgTypeRole).toInt();
    // display head picture as 24px
    QRect msgRect = option.rect;

    // user head picture displayed on the right side, conversation partner on the left side
    QRect headRect;
    QRect bubbleRect;
    QRect textRect;
    QRect timeRect;
    QPixmap headPic(headStr);

    int textLen = painter->fontMetrics().width(message);
    font.setPixelSize(m_font_size - 4);
    int dateLen = QFontMetrics(font).width(dateStr);
    int dateHeight = QFontMetrics(font).height();
    int padding = 10;
    // TODO
    int availableLen = msgRect.width() - ITEM_HEAD_SIZE * 2 - 4 * padding;
    int textHeight = (textLen / availableLen + 1) * painter->fontMetrics().height();
    textLen = textLen > availableLen ? availableLen : textLen;

    if (orientation == Unit::Right)
    {
        headRect = QRect(msgRect.right() - padding - ITEM_HEAD_SIZE, msgRect.top() + 2 * padding, ITEM_HEAD_SIZE, ITEM_HEAD_SIZE);
        bubbleRect = QRect(headRect.left() - textLen - padding * 1.5, msgRect.top() + padding * 3, textLen + padding, textHeight + padding);
        textRect = QRect(bubbleRect.left() + padding / 2, bubbleRect.top() + padding / 2, textLen, textHeight);
        timeRect = QRect(headRect.left() - padding / 2 - dateLen, msgRect.top() + padding, dateLen, dateHeight);
    }
    else
    {
        headRect = QRect(msgRect.left() + padding, msgRect.top() + 2 * padding, ITEM_HEAD_SIZE, ITEM_HEAD_SIZE);
        bubbleRect = QRect(headRect.right() + padding / 2, msgRect.top() + 3 * padding, textLen + padding, textHeight + padding);
        textRect = QRect(bubbleRect.left() + padding / 2, bubbleRect.top() + padding / 2, textLen, textHeight);
        timeRect = QRect(headRect.right() + padding / 2, msgRect.top() + padding, dateLen, dateHeight);
    }

    // TODO：how to send pic in conversation
    // head picture
    painter->drawPixmap(headRect, headPic);
    painter->setPen(Qt::white);
    // TODO: changeable bubble color
    QPainterPath path;
    path.addRoundedRect(bubbleRect, 5, 5);
    painter->fillPath(path, QColor(64, 64, 64));
    // text and time
    font.setPixelSize(m_font_size);
    painter->setFont(font);
    painter->drawText(textRect, message);
    font.setPixelSize(m_font_size - 4);
    painter->setFont(font);
    // TODO: not always display message send time
    painter->drawText(timeRect, dateStr);

    // TODO: display conversation time like qq does

    // painter->drawRect(msgRect);

    painter->restore();
}

QSize MessageDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(200, m_height);
}
