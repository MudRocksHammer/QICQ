#ifndef QQPOPMENUWIDGET_H
#define QQPOPMENUWIDGET_H

#include "customwidget.h"
#include <QMenu>
#include <QMouseEvent>

class QQPopMenuWidget : public CustomWidget
{
    Q_OBJECT

public:
    QQPopMenuWidget(QWidget* parent = 0);

signals:
    void on_popMenuWillSohw(QQPopMenuWidget* widget, QMenu* menu);

public:
    void setPopMenu(QMenu* menu);

protected slots:

protected:
    QMenu* popMenu;

public:
    void mousePressEvent(QMouseEvent* e) override;
};

#endif // QQPOPMENUWIDGET_H
