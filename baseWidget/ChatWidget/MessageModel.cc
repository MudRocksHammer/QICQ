#include "MessageModel.h"

MessageModel::MessageModel(QObject *parent) : QAbstractListModel(parent)
{
}

void MessageModel::setInfo(QVector<ItemInfo> &infos)
{
    beginResetModel();
    m_infos = infos;
    endResetModel();
}

void MessageModel::addInfos(QVector<ItemInfo> &infos, int row)
{
    beginInsertRows(QModelIndex(), row, infos.size());
    for (int i = 0; i < infos.size(); i++)
    {
        m_infos.push_front(infos[i]);
    }
    endInsertRows();
}

void MessageModel::addInfo(const ItemInfo &info)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_infos.append(info);
    endInsertRows();
}

QVariant MessageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const ItemInfo info = m_infos.at(index.row());
    switch (role)
    {
    case ItemInfo::UserNameRole:
        return info.getUserName();
    case ItemInfo::HeadRole:
        return info.getHeadPic();
    case ItemInfo::DateTimeRole:
        return info.getDateTime();
    case ItemInfo::MessageRole:
        return info.getMessage();
    case ItemInfo::OrientationRole:
        return info.getOrientation();
    case ItemInfo::MsgTypeRole:
        return info.getMessageType();
    default:
        return QVariant();
    }
}

int MessageModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_infos.size();
}
