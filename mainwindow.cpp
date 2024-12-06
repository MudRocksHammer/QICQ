#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : CustomMoveWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initUI();
    initConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAutoFillBackground(true);

    setWindowIcon(QIcon(":/resource/images/x_white.png"));
    setWindowTitle("QICQ");

    QFile file(":/resource/qss/mainwindow.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(file.readAll());
    file.close();

    ui->search_edit->setIcon(":/resource/common/search.png");

    // QTimer::singleShot(0, this, [&](){
    //     ui->search_edit->enableClear(true);
    //     qDebug() << ui->search_edit->width();
    // });


}

void MainWindow::initConnect()
{
    connect(ui->close_btn, &QPushButton::clicked, [this]{
        this->close();
    });

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::pushBtn_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::pushBtn3_clicked);
}

void MainWindow::pushBtn_clicked()
{
    stackedWidgetChanged(1);
}


void MainWindow::pushBtn3_clicked()
{
    stackedWidgetChanged(0);
}

void MainWindow::stackedWidgetChanged(int index)
{    
    ui->stackedWidget->setLength(ui->stackedWidget->width(),
     index > s_index?AnimationStackedWidget::LeftToRight:AnimationStackedWidget::RightToLeft);

    ui->stackedWidget->start(index);
    s_index = index;
}
