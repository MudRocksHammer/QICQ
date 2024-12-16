#pragma once

#include <QStyledItemDelegate>
#include <QPainter>

#include "../../comapi/unit.h"
#include "iteminfo.h"

class MessageDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    MessageDelegate(QObject *parent = 0);

protected:
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

private:
    int m_height;
    int m_font_size;
};