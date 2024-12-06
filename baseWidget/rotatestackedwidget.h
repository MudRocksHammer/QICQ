#ifndef ROTATESTACKEDWIDGET_H
#define ROTATESTACKEDWIDGET_H

#include <QStackedWidget>
#include <QVariant>
#include <QWidget>
#include <QPropertyAnimation>
#include <QTransform>
#include <QParallelAnimationGroup>
#include <QLabel>
#include <QPainter>

class RotateStackedWidget : public QStackedWidget
{
    Q_OBJECT
    Q_PROPERTY(float rotateVal READ getRotateVal WRITE setRotateVal)
public:
    explicit RotateStackedWidget(QWidget* parent = 0);
    ~RotateStackedWidget();

    void paintEvent(QPaintEvent* event);

    void rotate(int index);
    float getRotateVal();
    void setRotateVal(float rv);

public slots:
    void nextPage();

private slots:
    void valChanged(QVariant);
    void animationDone();

private:
    float rotateVal;
    bool isRotating;
    int nextIndex;
};

#endif // ROTATESTACKEDWIDGET_H
