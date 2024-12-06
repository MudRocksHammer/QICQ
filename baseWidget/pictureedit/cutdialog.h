#ifndef CUTDIALOG_H
#define CUTDIALOG_H

#include <QFrame>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>

class CutDialog : public QFrame
{
    Q_OBJECT
public:
    explicit CutDialog(QWidget* parent = 0);
    ~CutDialog();

private:
    QRect getResizeGem(QRect oldGeo, QPoint mousePoint);

signals:
    void needMove(int dwidth, int dheight);
    void signalMoved();

protected:
    void mousePressEvent(QMouseEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;
    void resizeEvent(QResizeEvent* e) override;
    void paintEvent(QPaintEvent *e) override;

private:
    QPoint m_startPoint;
    QPoint m_oldPos;
    bool m_isMoving;
    bool m_mouseDown;
    bool m_left;
    bool m_right;
    bool m_bottom;
    bool m_top;
    QLabel* m_label;
};

#endif // CUTDIALOG_H
