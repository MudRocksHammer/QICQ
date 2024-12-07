#ifndef ANIMATIONSTACKEDWIDGET_H
#define ANIMATIONSTACKEDWIDGET_H

#include <QStackedWidget>
#include <QPainter>
#include <QPropertyAnimation>

class AnimationStackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
    enum AnimationType{
        TopToBottom,
        BottomToTop,
        LeftToRight,
        RightToLeft
    };
    explicit AnimationStackedWidget(QWidget* parent = 0);
    virtual ~AnimationStackedWidget();

    static QString getClassName();
    void start(int index);
    void setIndex(int previous, int current);
    void setLength(int length, AnimationType type);
    void setDuration(int duration);
    int getDuration() const;

protected:
    void paintEvent(QPaintEvent* e) override;
    void renderPreviousWidget(QPainter& painter, QTransform& trans);
    void renderCurrentWidget(QPainter& painter, QTransform& trans);

private slots:
    void valueChanged_slot(const QVariant& value);
    void animationFinished_slot();

private:
    bool isAnimating;
    float m_curVal;
    int m_curIndex;
    int m_prevIndex;
    AnimationType m_type;
    QPropertyAnimation* m_anime;

};  

#endif // ANIMATIONSTACKEDWIDGET_H
