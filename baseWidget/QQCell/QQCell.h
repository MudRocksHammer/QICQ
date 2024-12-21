#pragma once

#include <QWidget>
#include <QListView>
#include <QVBoxLayout>
#include <QFile>

#include "QQCellLine.h"
#include "QQCellModel.h"
#include "QQCellDelegate.h"
#include "QQCellTitle.h"

class QQCell : public QWidget
{
    Q_OBJECT
public:
    QQCell(QWidget *parent = 0);
    void setData(QVector<Cell> &cell);
    void addData(const Cell &cell);

protected:
private:
    void initUI();

signals:
    void cellDoubleClicked_signal(QString);

private slots:
    void titleClicked_slot(bool);

private:
    QListView *m_listView;
    QQCellModel *m_model;
    QQCellDelegate *m_delegate;
    QQCellTitle *m_title;
};
