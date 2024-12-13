#include "QQCellModel.h"

QQCellModel::QQCellModel(QObject *parent) : QAbstractListModel(parent)
{
}

void QQCellModel::setData(QVector<Cell> &cells)
{
    beginResetModel();
    m_cells = cells;
    endResetModel();
}

void QQCellModel::addData(const Cell &cell)
{
    // beginInsertRows(QModelIndex())
}

QVariant QQCellModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    const Cell cell = m_cells.at(index.row());
    switch (role)
    {
    case Cell::HeadRole:
        return cell.getHead();
    case Cell::NameRole:
        return cell.getName();
    case Cell::StateRole:
        return cell.getState();
    case Cell::StaPicRole:
        return cell.getStaPic();
    case Cell::TimeStampRole:
        return cell.getLastTime();
    case Cell::CtrlPicRole:
        return cell.getCtrlPic();
    default:
        return QVariant();
    }
}

int QQCellModel::rowCount(const QModelIndex &index) const
{
    if (index.isValid())
        return 0;
    return m_cells.size();
}
