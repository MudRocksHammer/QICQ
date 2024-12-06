#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent) : CustomMoveWidget(parent), ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    initUI();
    initConnection();

}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::initConnection()
{
    connect(ui->minimum_btn, &QPushButton::clicked, [this]{
        QRect startGeometry = geometry();
        QRect endGeometry = QRect(startGeometry.bottomLeft().x(),
                                  startGeometry.bottomLeft().y(),
                                  20, 20); // 最终目标为缩小到任务栏图标大小

        QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
        animation->setDuration(500); // 动画持续时间，500ms
        animation->setStartValue(startGeometry);
        animation->setEndValue(endGeometry);
        animation->setEasingCurve(QEasingCurve::InCubic); // 动画曲线
        connect(animation, &QPropertyAnimation::finished, this, &LoginWidget::showMinimized);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
        //this->showMinimized();
    });
    connect(ui->setting_btn, QOverload<bool>::of(&QPushButton::clicked), [this](bool check){
//        if(check)
//            ui->stackedWidget->setCurrentIndex(1);
//        else
//            ui->stackedWidget->setCurrentIndex(0);
        ui->stackedWidget->nextPage();
    });
    connect(ui->close_btn, &QPushButton::clicked, [this]{
        this->close();
    });

    connect(ui->login_btn, &QPushButton::clicked, this, &LoginWidget::on_loginBtnClicked);

    connect(ui->switch_btn, QOverload<bool>::of(&QPushButton::clicked), [this](bool check){
        bDaylight = check;
        update();
    });

    connect(ui->confirm_btn, &QPushButton::clicked, [this]{
        qDebug() << ui->serverIP_edit->text();
    });
}

void LoginWidget::initUI()
{
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground); //使透明生效
    setAutoFillBackground(true);

    QFile file(":/resource/qss/loginWidget.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(file.readAll());
    file.close();

    QPixmap backg_pix(":/resource/background/hello.png");
    ui->background_label->setPixmap(backg_pix.scaled(365, 90, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->head_label->setPixmap(QPixmap(":/resource/head/head-64.png"));
    ui->title_label->setPixmap(QPixmap(":/resource/background/app.png").scaled(30, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    
}

void LoginWidget::paintEvent(QPaintEvent *event)
{
    QPixmap pix;
    QPainter painter(this);
    QRect rect = this->rect();

    QPainterPath path;
    path.addRoundedRect(rect, 10, 10);
    painter.setClipPath(path);

    if(bDaylight){
        pix.load(":/resource/background/daylight");
        painter.drawPixmap(QRect(0, 0, 460, 380), pix.scaled(460, 380));
    }
    else{
        pix.load(":/resource/background/moutain.jpg");
        painter.drawPixmap(0, 0, pix.copy(0, 800, 460, 380));
    }

}

void LoginWidget::keyPressEvent(QKeyEvent *e)
{
    QWidget::keyPressEvent(e);

    //qDebug() << "enter key pressed event" << e->key();
    if(e->key() == Qt::Key_Left){
        qDebug() << " left lfet";
    }
}

void LoginWidget::on_loginBtnClicked()
{
    MainWindow* main_win = new MainWindow();
    main_win->show();
    this->close();
}
