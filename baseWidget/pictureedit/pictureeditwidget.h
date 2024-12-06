#ifndef PICTUREEDITWIDGET_H
#define PICTUREEDITWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

#include "photoshotdialog.h"

class CutDialog;
class PhotoshotDialog;

namespace Ui {
class PictureEditWidget;
}

class PictureEditWidget : public QWidget
{
    Q_OBJECT
public:
    PictureEditWidget(QWidget* parent = 0);
    ~PictureEditWidget();

protected:
    void changeEvent(QEvent* e);

private:
    void loadPicture();

private slots:
    void cutDialog_slot(QRect rect);

    void on_load_btn_clicked();

    void on_save_btn_clicked();

private:
    Ui::PictureEditWidget* ui;

    QPixmap scaledPix;
    PhotoshotDialog* pdialog;
};

#endif // PICTUREEDITWIDGET_H
