#ifndef QQLISTVIEWGROUP_H
#define QQLISTVIEWGROUP_H

#include <QWidget>
#include <QMenu>
#include <QMouseEvent>

#include "qqcell.h"
#include "qqpopmenuwidget.h"
#include "ui_qqlistviewgroup.h"

namespace Ui{
class QQListViewGroup;
}

class QQListViewGroup : public QQPopMenuWidget
{
    Q_OBJECT
public:
    explicit QQListViewGroup(QQPopMenuWidget* parent = 0);
    ~QQListViewGroup();

public:
    void setQQCell(QQCell* c);

signals:
    void on_groupOpenStatusDidChanged(QQListViewGroup* group);

protected:
    void mousePressEvent(QMouseEvent *e) override;

public:
    Ui::QQListViewGroup* ui;

private:
    QQCell* cell;
};

#endif // QQLISTVIEWGROUP_H
