#include "qqlistviewchild.h"

QQListViewChild::QQListViewChild(QQPopMenuWidget* parent) : QQPopMenuWidget(parent)
{
    m_bEntered = false;
}

QQListViewChild::~QQListViewChild(){

}

void QQListViewChild::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        emit on_childDidSelected(this);
    }
    else if(Qt::RightButton == e->button()){
        if(NULL == this->cell) return;
        Q_EMIT signalRightClicked(this->cell);
        QQPopMenuWidget::mousePressEvent(e);
    }
}

void QQListViewChild::mouseDoubleClickEvent(QMouseEvent *e){
    emit on_childDidDoubleClicked(this->cell);
}

void QQListViewChild::enterEvent(QEvent *e){
    m_bEntered = true;
    update();
    QWidget::enterEvent(e);
}

void QQListViewChild::leaveEvent(QEvent *e){
    m_bEntered = false;
    update();
    QWidget::leaveEvent(e);
}

void QQListViewChild::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillRect(this->rect(), m_bEntered?QColor("#D9D8D7"):QColor("transparent"));
    QPixmap pixmap(cell->iconPath);
    if(pixmap.isNull()) pixmap = QPixmap(":/resouce/head/1.bmp");

    //如果当前是离线绘制灰度图
    if(OffLine == cell->status)
        pixmap = myHelper::ChangeGrayPixmap(pixmap.toImage());

    //绘制头像
    painter.drawPixmap(10, 10, 40 ,40, pixmap);

    int w = this->rect().width();
    int h = this->rect().height();

    QFont font("SimHei", 14);
    QPen pen;

    //绘制名字
    pen.setColor(QColor("#000000"));
    font.setPixelSize(12);
    painter.setPen(pen);
    painter.setFont(font);
    painter.drawText(70, 0, 2 - 70, h / 2 - 2, Qt::AlignBottom, cell->name);

    //绘制subtitle
    pen.setColor(QColor("#666666"));
    font.setPixelSize(10);
    painter.setPen(pen);
    painter.setFont(font);
    painter.drawText(70, h / 2 + 2, w - 70, h / 2 - 2, Qt::AlignTop, cell->subTitle);
}
