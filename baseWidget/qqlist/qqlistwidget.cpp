#include "qqlistwidget.h"

QQListWidget::QQListWidget(QWidget* parent) : QListWidget(parent)
{
    m_nRightClickedCell = nullptr;
}

QQCell* QQListWidget::getRightClickedCell(){
    return m_nRightClickedCell;
}

void QQListWidget::setGroupPopMenu(QMenu *menu){
    mGroupMenu = menu;
}

void QQListWidget::setChildPopMenu(QMenu *menu){
    mChildMenu = menu;
}

void QQListWidget::insertQQCell(QQCell *cell){
    if(cell->type == QQCellType_Group || cell->type == QQCellType_GroupEx){
        cells.append(cell);
    }
    else{
        for(auto group : cells){
            if(!group->groupName.compare(cell->groupName)){
                group->childs.append(cell);
                break;
            }
        }
    }
    upload();
}

void QQListWidget::removeQQCell(QQCell *cell){
    if(cell->type == QQCellType_Group || cell->type == QQCellType_GroupEx)
        cells.removeOne(cell);
    else{
        for(auto group : cells){
            if(!group->groupName.compare(cell->groupName)){
                group->childs.removeOne(cell);
                break;
            }
        }
    }
    upload();
}

void QQListWidget::upload(){
    this->clear();
    for(auto cell: cells){
        if(cell->type == QQCellType_Group || cell->type == QQCellType_GroupEx){
            QQListViewGroup* group = new QQListViewGroup();
            group->setGeometry(0, 0, 300, 30);
            if(cell->type == QQCellType_Group){
                //获取在线好友
                int nOnlineCnt = 0;
                for(auto child: cell->childs){
                    if(OnLine == child->status)
                        nOnlineCnt ++;
                }
                group->ui->groupTitleLabel->setText(cell->groupName);
                group->ui->groupSubTitleLabel->setText(QString("[%1 %2]").arg(nOnlineCnt).arg(cell->childs.size()));
            }
            else{
                group->ui->groupTitleLabel->setText(QString("%1[%2/%2]").arg(cell->groupName).arg(cell->childs.size()));
                group->ui->groupSubTitleLabel->setText(QString(""));
            }
            group->setQQCell(cell);
            group->setPopMenu(mGroupMenu);
            connect(group, &QQListViewGroup::on_groupOpenStatusDidChanged, this, &QQListWidget::on_groupOpenDidChanged_slot);
            connect(group, &QQListViewGroup::on_popMenuWillSohw, this, &QQListWidget::on_popmenuWillShow_slot);

            QListWidgetItem* item = new QListWidgetItem("");
            this->addItem(item);
            this->setItemWidget(item, group);
            item->setSizeHint(group->geometry().size());

            if(cell->isOpen){
                //显示在线好友
                for(auto ccell:cell->childs){
                    if(OnLine == ccell->status)
                        addChildItem(ccell);
                }

                //显示离线好友
                for(auto ccell: cell->childs){
                    if(OffLine == ccell->status)
                        addChildItem(ccell);
                }
            }
        }
    }
}

void QQListWidget::on_groupOpenDidChanged_slot(QQListViewGroup* ){
    upload();
}

void QQListWidget::on_childDidSelected_slot(QQListViewChild* child){
    Q_UNUSED(child);
}

void QQListWidget::setBackGroundColor(QWidget *widget, int index){
    widget->setStyleSheet(index % 2 ? "QWidget{background:rgb(100, 100, 100, 100)}":
        "QWidget{background:rgb(255,255,255)}");
}

void QQListWidget::addChildItem(QQCell *cell){
    QQListViewChild* child = new QQListViewChild;
    child->setGeometry(0, 0, 300, 60);
    child->cell = cell;
    child->setPopMenu(mChildMenu);
    connect(child, &QQListViewChild::on_childDidSelected, this, &QQListWidget::on_childDidSelected_slot);
    connect(child, &QQListViewChild::on_childDidDoubleClicked, this, &QQListWidget::on_childDidDoubleClicked);
    connect(child, &QQListViewChild::signalRightClicked, this, &QQListWidget::cellRightClicked_slot);

    QListWidgetItem* item = new QListWidgetItem("");
    this->addItem(item);
    this->setItemWidget(item, child);
    item->setSizeHint(child->geometry().size());
}

QQCell* QQListWidget::getGroupForName(QString *groupName){
    for(auto it : cells){
        if(!it->groupName.compare(groupName)){
            return it;
        }
    }

    return nullptr;
}

void QQListWidget::on_popmenuWillShow_slot(QQPopMenuWidget* widget, QMenu* menu){
    emit on_popmenuWillShow(this, widget, menu);
}

void QQListWidget::cellRightClicked_slot(QQCell* cell){
    m_nRightClickedCell = cell;
}

QList<QQCell*> QQListWidget::getCells() const{
    return cells;
}
