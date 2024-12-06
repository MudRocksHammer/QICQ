#ifndef QQLISTWIDGET_H
#define QQLISTWIDGET_H

#include <QListWidget>
#include <QList>
#include <QHash>
#include <QMenu>

#include "qqcell.h"
#include "qqlistviewchild.h"
#include "qqlistviewgroup.h"

class QQListWidget : public QListWidget
{
    Q_OBJECT
public:
    QQListWidget(QWidget* parent = 0);
    ~QQListWidget() {}

    QQCell* getRightClickedCell();

signals:
    void on_popmenuWillShow(QQListWidget* listWidget, QQPopMenuWidget* popWidget, QMenu* menu);
    void on_childDidDoubleClicked(QQCell* cell);

public slots:
    void on_groupOpenDidChanged_slot(QQListViewGroup* group);
    void on_childDidSelected_slot(QQListViewChild* child);
    void on_popmenuWillShow_slot(QQPopMenuWidget* widget, QMenu* menu);
    void cellRightClicked_slot(QQCell* cell);

private:
    QList<QQCell*> cells;
    QMenu* mGroupMenu;
    QMenu* mChildMenu;

    QQCell* m_nRightClickedCell;

public:
    void insertQQCell(QQCell* cell);
    void removeQQCell(QQCell* cell);
    void upload();
    QQCell* getGroupForName(QString* groupName);

    void setGroupPopMenu(QMenu* menu);
    void setChildPopMenu(QMenu* menu);

    QList<QQCell*> getCells() const;

private:
    void setBackGroundColor(QWidget* widget, int index);
    void addChildItem(QQCell* cell);
};

#endif // QQLISTWIDGET_H
