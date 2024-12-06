#ifndef PHOTOSHOTDIALOG_H
#define PHOTOSHOTDIALOG_H

#include <QWidget>
#include "cutdialog.h"
#include <QDebug>

class CurDialog;

class PhotoshotDialog : public QWidget
{
    Q_OBJECT
public:
    explicit PhotoshotDialog(QWidget* parent = 0);
    ~PhotoshotDialog();
    QRect getShotGeometry() { return dialog->geometry(); }

signals:
    void signalMoved(QRect rect);

private:
    CutDialog* dialog;

private slots:
    void cutDlgMoved_slot();

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // PHOTOSHOTDIALOG_H
