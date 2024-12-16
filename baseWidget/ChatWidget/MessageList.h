#pragma once

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QListView>
#include <QFile>

#include "ItemInfo.h"
#include "MessageDelegate.h"
#include "MessageModel.h"

class MessageList : public QWidget
{
    Q_OBJECT
public:
    MessageList(QWidget *parent = 0);
    void addText(const ItemInfo &text);
    void addTexts(QVector<ItemInfo> &texts);
    void setMessage(QVector<ItemInfo> &mes);
    void scrollToBottom();

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    void initUI();

private:
    MessageDelegate *m_delegate;
    MessageModel *m_model;
    QListView *m_listview;
};