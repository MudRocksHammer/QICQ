#include "qqlistviewgroup.h"


QQListViewGroup::QQListViewGroup(QQPopMenuWidget* parent)
    : QQPopMenuWidget(parent), ui(new Ui::QQListViewGroup)
{
    ui->setupUi(this);

    this->setFixedHeight(25);

    ui->groupSubTitleLabel->setAlignment(Qt::AlignRight);
}

QQListViewGroup::~QQListViewGroup(){
    delete ui;
}

void QQListViewGroup::setQQCell(QQCell *c){
    cell = c;
    if(cell->isOpen){
        ui->groupIconLabel->setPixmap(QPixmap(":/resource/common/aio_arrow_down.png"));
    }
    else{
        ui->groupIconLabel->setPixmap(QPixmap(":/resouce/common/aio_arrow_right.png"));
    }
}

void QQListViewGroup::mousePressEvent(QMouseEvent *e){
    QQPopMenuWidget::mousePressEvent(e);

    if(e->button() != Qt::LeftButton) return;

    if(cell == nullptr) return;

    cell->isOpen = !cell->isOpen;
    if(cell->isOpen){
        ui->groupIconLabel->setPixmap(QPixmap(":/resource/common/aio_arrow_down.png"));
    }
    else{
        ui->groupIconLabel->setPixmap(QPixmap(":/resource/common/aio_arrow_right.png"));
    }

    Q_EMIT on_groupOpenStatusDidChanged(this);
}
