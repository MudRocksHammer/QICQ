#include "rotatestackedwidget.h"

RotateStackedWidget::RotateStackedWidget(QWidget* parent) : QStackedWidget(parent)
{
    rotateVal = 0;
    isRotating = false;
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

RotateStackedWidget::~RotateStackedWidget(){

}

void RotateStackedWidget::paintEvent(QPaintEvent *event){
    if(isRotating){
        if(rotateVal > 90){
            QPixmap pixmap(widget(nextIndex)->size());
            widget(nextIndex)->render(&pixmap);
            QPainter painter(this);

            QTransform transform;
            transform.translate(width() / 2, 0);
            transform.rotate(rotateVal + 180, Qt::YAxis);
            painter.setTransform(transform);
            painter.drawPixmap(-1 * width() / 2, 0, pixmap);
        }
        else{
            QPixmap pixmap(currentWidget()->size());
            currentWidget()->render(&pixmap);
            QPainter painter(this);

            QTransform transform;
            transform.translate(width() / 2, 0);
            transform.rotate(rotateVal, Qt::YAxis);
            painter.setTransform(transform);
            painter.drawPixmap(-1 * width() / 2, 0, pixmap);
        }
    }
    else{
        QWidget::paintEvent(event);
    }
}

void RotateStackedWidget::nextPage(){
    rotate((currentIndex() + 1) >= count() ? 0 : (currentIndex()+1));
}

void RotateStackedWidget::rotate(int index){
    if(isRotating) return;
    nextIndex = index;
    int offset_x = frameRect().width();
    int offset_y = frameRect().height();
    widget(index)->setGeometry(0, 0, offset_x, offset_y);

    QPropertyAnimation* anime = new QPropertyAnimation(this, "rotateVal");
    anime->setDuration(500);
    anime->setEasingCurve(QEasingCurve::Linear);
    anime->setStartValue(0);
    anime->setEndValue(180);
    connect(anime, &QPropertyAnimation::valueChanged, this, &RotateStackedWidget::valChanged);
    connect(anime, &QPropertyAnimation::finished, this, &RotateStackedWidget::animationDone);
    currentWidget()->hide();
    isRotating = true;
    anime->start();
}

float RotateStackedWidget::getRotateVal(){
    return rotateVal;
}

void RotateStackedWidget::setRotateVal(float rv){
    rotateVal = rv;
}

void RotateStackedWidget::valChanged(QVariant)
{
    update();
}

void RotateStackedWidget::animationDone(){
    rotateVal = 0;
    isRotating = false;
    widget(nextIndex)->show();
    widget(nextIndex)->raise();
    setCurrentWidget(widget(nextIndex));
    update();
}
