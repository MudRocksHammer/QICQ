#pragma once

#include <QAbstractItemDelegate>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QFontMetrics>

#include "QQCellLine.h"

class QQCellDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    QQCellDelegate(QObject *parent = 0);

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option, const QModelIndex &index) override;

signals:
    void cellDoubleClicked_signal(QString);
};