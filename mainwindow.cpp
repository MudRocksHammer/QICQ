#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : CustomMoveWidget(parent), ui(new Ui::MainWindow), m_direction(ResizeDirection::None)
{
    ui->setupUi(this);

    initSysTrayIcon();
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

    m_chatWidget = new QWidget(this);
    m_chatWidget->setStyleSheet("background-color : yellow");
    ui->horizontalLayout_3->addWidget(m_chatWidget);
    m_chatWidget->show();
    m_chatWidget->setMouseTracking(true);
    // QTimer::singleShot(0, this, [&](){
    //     ui->search_edit->enableClear(true);
    //     qDebug() << ui->search_edit->width();
    // });

    // TODO: temporary list view display, handle later
    QVector<Cell> myCells = {
        {"Show case1", ":/resource/head/3.bmp", "I feel more powerful when I learn more", "", "", ""},
        {"Show case2", ":/resource/head/4.bmp", "Time is all you got valuable, spend it wisely", "", "", ""},
        {"Show case3", ":/resource/head/5.bmp", "Im the storm that is approaching", "", "", ""}};

    QQCell *cell = new QQCell(this);
    cell->setData(myCells);

    ui->stackedWidget->addWidget(new QWidget(this));
    ui->stackedWidget->widget(2)->setLayout(new QVBoxLayout(this));
    ui->stackedWidget->widget(2)->layout()->setMargin(0);
    ui->stackedWidget->widget(2)->layout()->addWidget(cell);
}

void MainWindow::initConnect()
{
    connect(ui->close_btn, &QPushButton::clicked, [this]
            { this->close(); });

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::pushBtn_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::pushBtn3_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::pushBtn2_clicked);

    connect(ui->conv_btn, &QPushButton::clicked, this, &MainWindow::conv_btn_clicked);
    connect(ui->contact_btn, &QPushButton::clicked, this, &MainWindow::contact_btn_clicked);
}

void MainWindow::enterEvent(QEvent *e)
{
    setCursor(Qt::ArrowCursor);
}

void MainWindow::leaveEvent(QEvent *e)
{
    setCursor(Qt::ArrowCursor);
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if (onHorizontalEdge(e->pos()))
    {
        if (e->pos().x() - rect().left() < 15)
            m_direction = ResizeDirection::Left;
        else
            m_direction = ResizeDirection::Right;
    }
    else if (onVerticalEdge(e->pos()))
    {
        if (e->pos().y() - rect().top() < 15)
            m_direction = ResizeDirection::Top;
        else
            m_direction = ResizeDirection::Bottom;
    }
    else
        m_direction = ResizeDirection::None;
    CustomMoveWidget::mousePressEvent(e);
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    // widget resize or move
    // TODO: 缩放到一定大小chatwidget显示或消失
    if (m_mousePressed)
    {
        QPoint delta = e->pos() - mousePoint;
        switch (m_direction)
        {
        case ResizeDirection::Left:
            if (width() == minimumWidth() && delta.x() > 0)
                break;
            setGeometry(x() + delta.x(), y(), width() - delta.x(), height());
            setCursor(Qt::SizeHorCursor);
            break;
        case ResizeDirection::Right:
            setGeometry(x(), y(), width() + delta.x(), height());
            mousePoint = e->pos();
            setCursor(Qt::SizeHorCursor);
            break;
        case ResizeDirection::Top:
            if (height() == minimumHeight() && delta.y() > 0)
                break;
            setGeometry(x(), y() + delta.y(), width(), height() - delta.y());
            setCursor(Qt::SizeVerCursor);
            break;
        case ResizeDirection::Bottom:
            setGeometry(x(), y(), width(), height() + delta.y());
            mousePoint = e->pos();
            setCursor(Qt::SizeVerCursor);
            break;
        default:
            CustomMoveWidget::mouseMoveEvent(e);
            unsetCursor();
            break;
        }
    }
    else
    {
        if (onHorizontalEdge(e->pos()))
            setCursor(Qt::SizeHorCursor);
        else if (onVerticalEdge(e->pos()))
            setCursor(Qt::SizeVerCursor);
        else
            unsetCursor();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    unsetCursor();
    CustomMoveWidget::mouseReleaseEvent(e);
}

void MainWindow::pushBtn_clicked()
{
    stackedWidgetChanged(1);
}

void MainWindow::pushBtn3_clicked()
{
    stackedWidgetChanged(0);
}

void MainWindow::conv_btn_clicked(bool check)
{
    stackedWidgetChanged(0);
}

void MainWindow::contact_btn_clicked(bool check)
{
    stackedWidgetChanged(2);
}

void MainWindow::pushBtn2_clicked()
{
    m_chatWidget->setVisible(!m_chatWidget->isVisible());
}

void MainWindow::stackedWidgetChanged(int index)
{
    ui->stackedWidget->setLength(ui->stackedWidget->width(),
                                 index > s_index ? AnimationStackedWidget::LeftToRight : AnimationStackedWidget::RightToLeft);

    ui->stackedWidget->start(index);
    s_index = index;
}

void MainWindow::trayIcon_clicked_slot(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
        break;
    case QSystemTrayIcon::DoubleClick:
        if (!this->isVisible())
            this->show();
        break;
    default:
        break;
    }
}

void MainWindow::trayMenu_clicked_slot(QAction *action)
{
    if (action->text() == ("Exit"))
    {
        m_bQuit = true;
        // tcp断开
        this->hide();
        QTimer::singleShot(500, this, [this]
                           {
            //close all chat widgets
            //delete tcp
            qApp->quit(); });
    }
    else if (action->text() == ("Show Main Window"))
    {
        this->show();
    }
    else if (action->text() == ("Online"))
    {
    }
    else if (action->text() == ("Hide"))
    {
    }
    else if (action->text() == ("Away"))
    {
    }
    else if (action->text() == ("Busy"))
    {
    }
    else if (action->text() == ("Offline"))
    {
    }
    else if (action->text() == ("Turn Off Sound"))
    {
    }
    else if (action->text() == ("Stop Blinking"))
    {
    }
}

void MainWindow::initSysTrayIcon()
{
    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setIcon(QIcon(":/resource/images/x_white.png"));

    QMenu *menu = new QMenu(this);
    menu->addAction(new QAction(QIcon(":/resource/common/online.png"), "Online", this));
    menu->addAction(new QAction(QIcon(":/resource/common/hide.png"), "Hide", this));
    menu->addAction(new QAction(QIcon(":/resource/common/away.png"), "Away", this));
    menu->addAction(new QAction(QIcon(":/resource/common/busy.png"), "Busy", this));
    menu->addAction(new QAction(QIcon(":/resource/common/offline.png"), "Offline", this));
    menu->addSeparator();
    menu->addAction("Turn Off Sound");
    menu->addAction("Stop Blink");
    menu->addSeparator();
    menu->addAction("Show Main Window");
    menu->addAction("Exit");

    QFile file(":/resource/qss/traymenu.qss");
    file.open(QFile::ReadOnly);
    menu->setStyleSheet(file.readAll());
    file.close();

    m_trayIcon->setContextMenu(menu);
    m_trayIcon->show();

    connect(m_trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::trayIcon_clicked_slot);
    connect(menu, &QMenu::triggered, this, &MainWindow::trayMenu_clicked_slot);
}

bool MainWindow::onHorizontalEdge(QPoint pos)
{
    QRect rect = this->rect();
    if ((pos.x() - rect.left() < 15) || (rect.right() - pos.x() < 15))
        return true;
    return false;
}

bool MainWindow::onVerticalEdge(QPoint pos)
{
    QRect rect = this->rect();
    if (pos.y() - rect.top() < 15 || rect.bottom() - pos.y() < 15)
        return true;
    return false;
}
