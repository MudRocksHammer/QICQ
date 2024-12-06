#ifndef QQLISTVIEWCHILD_H
#define QQLISTVIEWCHILD_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QEvent>
#include <QPainter>

#include "gloabal.h"
#include "qqcell.h"
#include "qqpopmenuwidget.h"

class QQListViewChild : public QQPopMenuWidget
{
    Q_OBJECT
public:
    explicit QQListViewChild(QQPopMenuWidget* parent = 0);
    ~QQListViewChild();

signals:
    void on_childDidSelected(QQListViewChild* child);
    void on_childDidDoubleClicked(QQCell* cell);
    void signalRightClicked(QQCell* cell);

protected:
    void mousePressEvent(QMouseEvent* e);
    void mouseDoubleClickEvent(QMouseEvent* e);
    void enterEvent(QEvent* e);
    void leaveEvent(QEvent* e);

    void paintEvent(QPaintEvent*);

public:
    QQCell* cell;

private:
    bool m_bEntered;
};

#endif // QQLISTVIEWCHILD_H
