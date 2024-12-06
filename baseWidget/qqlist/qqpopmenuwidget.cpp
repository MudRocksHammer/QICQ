#include "qqpopmenuwidget.h"

QQPopMenuWidget::QQPopMenuWidget(QWidget* parent) : CustomWidget(parent)
{

}

void QQPopMenuWidget::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::RightButton){
        if(NULL == popMenu)
            return;

        emit on_popMenuWillSohw(this, popMenu);
        popMenu->exec(QCursor::pos());
    }
}

void QQPopMenuWidget::setPopMenu(QMenu *menu){
    popMenu = menu;
}
