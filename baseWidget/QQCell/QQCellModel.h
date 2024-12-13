#pragma once

#include <QAbstractListModel>
#include <QPainter>

#include "QQCellLine.h"

class QQCellModel : public QAbstractListModel
{
    Q_OBJECT
public:
    QQCellModel(QObject *parent = 0);

    void setData(QVector<Cell> &cells);
    void addData(const Cell &cell);

protected:
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &index = QModelIndex()) const override;

private:
    QVector<Cell> m_cells;
};