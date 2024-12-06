#include "photoshotdialog.h"

PhotoshotDialog::PhotoshotDialog(QWidget* parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);

    dialog = new CutDialog(this);
    dialog->show();
    setGeometry(0, 0, parentWidget()->width(), parentWidget()->height());
    connect(dialog, &CutDialog::signalMoved, this, &PhotoshotDialog::cutDlgMoved_slot);
}

PhotoshotDialog::~PhotoshotDialog(){

}

void PhotoshotDialog::cutDlgMoved_slot(){
    Q_EMIT signalMoved(dialog->geometry());
}

void PhotoshotDialog::paintEvent(QPaintEvent *event){
    QPainterPath painterPath;
    QPainterPath p;
    p.addRect(x(), y(), rect().width(), rect().height());
    painterPath.addRect(dialog->geometry());
    QPainterPath drawPath = p.subtracted(painterPath);

    QPainter painter(this);
    painter.setOpacity(0.7);
    painter.fillPath(drawPath, QBrush(Qt::black));
}
