#pragma once

#include <QAbstractListModel>

#include "ItemInfo.h"

class MessageModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MessageModel(QObject *parent = 0);

    void setInfo(QVector<ItemInfo> &infos);
    /// @brief add multiple infos into model
    /// @param row
    /// @param infos
    /// @details display chat history partly at one time, when scroll view up, dynamically add display history
    void addInfos(QVector<ItemInfo> &infos, int row = 0);

    /// @brief add an iteminfo into model
    /// @param info
    /// @details when send text, use this to add and display
    void addInfo(const ItemInfo &info);

protected:
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

private:
    QVector<ItemInfo> m_infos;
};