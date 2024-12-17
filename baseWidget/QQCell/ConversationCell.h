#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QListView>
#include <QFile>

#include "QQCellLine.h"
#include "QQCellModel.h"
#include "QQCellDelegate.h"

class ConversationCell : public QWidget
{
    Q_OBJECT
public:
    ConversationCell(QWidget *parent = 0);

    void setData(QVector<Cell> &cell);
    void addData(const Cell &cell);

protected:
private:
    void initUI();

private:
    QQCellModel *m_model;
    QQCellDelegate *m_delegate;
    QListView *m_listview;
};