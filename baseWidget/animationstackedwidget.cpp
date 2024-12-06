#include "animationstackedwidget.h"

#include <QPixmap>
#include <QTransform>

AnimationStackedWidget::AnimationStackedWidget(QWidget *parent)
    : QStackedWidget(parent), isAnimating(false), m_curVal(0), m_curIndex(0), m_prevIndex(0), m_anime(new QPropertyAnimation(this, QByteArray()))
{
    m_anime->setDuration(500);
    m_anime->setEasingCurve(QEasingCurve::Linear);
    m_anime->setStartValue(0);
    m_anime->setEndValue(0);

    connect(m_anime, &QPropertyAnimation::valueChanged, this, &AnimationStackedWidget::valueChanged_slot);
    connect(m_anime, &QPropertyAnimation::finished, this, &AnimationStackedWidget::animationFinished_slot);
}

AnimationStackedWidget::~AnimationStackedWidget()
{
    delete m_anime;
}

QString AnimationStackedWidget::getClassName()
{
    return staticMetaObject.className();
}

void AnimationStackedWidget::start(int index)
{
    if(isAnimating) return;
    m_prevIndex = m_curIndex;
    m_curIndex = index;

    int offsetx = frameRect().width();
    int offsety = frameRect().height();
    widget(m_curIndex)->setGeometry(0, 0, offsetx, offsety);

    currentWidget()->hide();
    isAnimating = true;
    m_anime->start();
}

void AnimationStackedWidget::setIndex(int previous, int current)
{
    m_curIndex = current;
    m_prevIndex = previous;
}

void AnimationStackedWidget::setLength(int length, AnimationType type)
{
    switch(m_type = type){
        case BottomToTop:
        case LeftToRight:
            m_anime->setStartValue(-length/2);
            m_anime->setEndValue(length/2);
            break;
        case TopToBottom:
        case RightToLeft:
            m_anime->setStartValue(length/2);
            m_anime->setEndValue(-length/2);
            break;
        default: break;
    }
}

void AnimationStackedWidget::setDuration(int duration)
{
    m_anime->setDuration(duration);
}

int AnimationStackedWidget::getDurarion() const
{
    return m_anime->duration();
}

void AnimationStackedWidget::paintEvent(QPaintEvent *e)
{
    if (isAnimating){
        QPainter painter(this);
        QTransform trans;
        renderCurrentWidget(painter, trans);
        renderPreviousWidget(painter, trans);
    }
    else
    {
        QWidget::paintEvent(e);
    }
}

void AnimationStackedWidget::renderPreviousWidget(QPainter &painter, QTransform &trans)
{
    QWidget* w = widget(m_prevIndex);
    QPixmap pixmap(w->size());
    pixmap.fill(Qt::transparent);
    w->setAttribute(Qt::WA_TranslucentBackground, true);
    w->render(&pixmap);
    w->setAttribute(Qt::WA_TranslucentBackground, false);

    Q_UNUSED(trans);
    switch(m_type){
        case BottomToTop:
            painter.drawPixmap(0, height()/2, pixmap);
            break;
        case TopToBottom:
            painter.drawPixmap(0, -height()/2, pixmap);
            break;
        case LeftToRight:
            painter.drawPixmap(width() / 2, 0, pixmap);
            break;
        case RightToLeft:
            painter.drawPixmap(-width() / 2, 0, pixmap);
            break;
        default: break;
    }
}

void AnimationStackedWidget::renderCurrentWidget(QPainter &painter, QTransform &trans)
{
    QWidget* w = widget(m_curIndex);
    QPixmap pixmap(w->size());
    pixmap.fill(Qt::transparent);
    w->setAttribute(Qt::WA_TranslucentBackground, true);
    w->render(&pixmap);
    w->setAttribute(Qt::WA_TranslucentBackground, false);

    switch(m_type){
        case BottomToTop:
            trans.translate(0, m_curVal);
            painter.setTransform(trans);
            painter.drawPixmap(0, -height()/2, pixmap);
            break;
        case TopToBottom:
            trans.translate(0, m_curVal);
            painter.setTransform(trans);
            painter.drawPixmap(0, height()/2, pixmap);
            break;
        case LeftToRight:
            trans.translate(m_curVal, 0);
            painter.setTransform(trans);
            painter.drawPixmap(-width()/2, 0, pixmap);
            break;
        case RightToLeft:
            trans.translate(m_curVal, 0);
            painter.setTransform(trans);
            painter.drawPixmap(width()/2, 0, pixmap);
            break;
        default: break;
    }
}

void AnimationStackedWidget::valueChanged_slot(const QVariant &value)
{
    m_curVal = value.toFloat();
    update();
}

void AnimationStackedWidget::animationFinished_slot()
{
    m_curVal = 0;
    isAnimating = false;
    QWidget* w = widget(m_curIndex);
    w->show();
    w->raise();
    setCurrentWidget(w);
    update();
}
