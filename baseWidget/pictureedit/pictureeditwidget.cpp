#include "pictureeditwidget.h"
#include "ui_PictureEditWidget.h"

PictureEditWidget::PictureEditWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::PictureEditWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);

    //该类为剪切框
    pdialog = new PhotoshotDialog(ui->preview_widget);
    connect(pdialog, &PhotoshotDialog::signalMoved, this, &PictureEditWidget::cutDialog_slot);
}

PictureEditWidget::~PictureEditWidget(){
    delete ui;
}

void PictureEditWidget::changeEvent(QEvent *e){
    QWidget::changeEvent(e);
    switch(e->type()){
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void PictureEditWidget::loadPicture(){

}

void PictureEditWidget::cutDialog_slot(QRect rect){
    QPixmap pix = scaledPix.copy(rect);
    //剪出来的图片保存地址
    ui->sxs_label->setPixmap(pix.scaled(64, 64));
    ui->vxv_label->setPixmap(pix.scaled(48, 48));
}

void PictureEditWidget::on_load_btn_clicked()
{
    //加载图片
    static QString s_strPath = "./";
    QString str_file_name = QFileDialog::getOpenFileName(this, tr("选择图片"), s_strPath, tr("图片(*.jpg; *.png)"));
    //如果没有选择文件则退出
    if(str_file_name.isEmpty()){
        return ;
    }

    s_strPath = str_file_name;
    //原图地址
    QPixmap pixmap(str_file_name);
    if(!pixmap.isNull()){
        int nW = ui->load_widget->width();
        int nH = ui->load_widget->height();
        if((pixmap.width() > nW) && (pixmap.height() > nH)){
            ui->preview_widget->resize(QSize(nW, nH));
            scaledPix = pixmap.scaled(nW, nH, Qt::KeepAspectRatio);
        }
        else{
            ui->preview_widget->resize(pixmap.size());
            scaledPix = pixmap;
        }

        ui->preview_widget->setPixmap(scaledPix);
    }

    pdialog->show();
}

void PictureEditWidget::on_save_btn_clicked()
{
    QPixmap pixmap = scaledPix.copy(pdialog->getShotGeometry()).scaled(64, 64);
    if(!pixmap.isNull())
        pixmap.save("./head-64.png", "png");
    pixmap = scaledPix.copy(pdialog->getShotGeometry()).scaled(48, 48);
    if(!pixmap.isNull())
        pixmap.save("./head-48.png", "png");
}
