#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : CustomMoveWidget(parent), ui(new Ui::MainWindow), m_direction(Unit::ResizeDirection::None)
{
    ui->setupUi(this);

    initSysTrayIcon();
    initUI();
    initConnect();

    QFile file(":/resource/qss/mainwindow.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(file.readAll());
    file.close();
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

    ui->search_edit->setIcon(":/resource/common/search.png");

    m_chatWidget = new QWidget(this);
    ui->verticalLayout_3->addWidget(m_chatWidget);
    m_chatWidget->show();
    m_chatWidget->setMouseTracking(true);
    m_chatWidget->setLayout(new QVBoxLayout(m_chatWidget));
    m_chatWidget->setMinimumWidth(300);
    m_chatWidget->setObjectName("chatWidget");
    m_chatWidget->hide();
    QButtonGroup *grp = new QButtonGroup(this);
    grp->addButton(ui->contact_btn);
    grp->addButton(ui->conv_btn);

    connect(grp, QOverload<QAbstractButton *, bool>::of(&QButtonGroup::buttonToggled), this, &MainWindow::btnGrp_toggled);
    ui->conv_btn->setChecked(true);

    createContactArea("");
    createConversationArea("");
    // createChatWidget();
}

void MainWindow::initConnect()
{
    connect(ui->close_btn, &QPushButton::clicked, [this]
            { this->close(); });
}

void MainWindow::createContactArea(QString)
{
    // contact
    QVector<Cell> myCells = {
        {"Show case1", ":/resource/head/3.bmp", "I feel more powerful when I learn more", "", "", ""},
        {"Show case2", ":/resource/head/4.bmp", "Time is all you got valuable, spend it wisely", "", "", ""},
        {"Show case3", ":/resource/head/5.bmp", "Im the storm that is approaching", "", "", ""}};

    QQCell *cell = new QQCell(this);
    cell->setData(myCells);

    // ui->stackedWidget->addWidget(new QWidget(this));
    // ui->stackedWidget->widget(0)->setLayout(new QVBoxLayout(this));
    // ui->stackedWidget->widget(0)->layout()->setMargin(0);
    // ui->stackedWidget->widget(0)->layout()->addWidget(cell);
    ui->widget_3->layout()->addWidget(cell);
    connect(cell, &QQCell::cellDoubleClicked_signal, this, &MainWindow::cellDoubleClicked_slot);
}

void MainWindow::createConversationArea(QString)
{
    // conversation
    QVector<Cell> convCells = {
        {"Show case1", ":/resource/head/3.bmp", "Do you remember where did I put my keys?", QTime::currentTime().toString("hh:mm:ss"), "", ""},
        {"Show case2", ":/resource/head/4.bmp", "Time is all you got valuable, spend it wisely", QTime::currentTime().toString("hh:mm:ss"), "", ""},
        {"Show case3", ":/resource/head/5.bmp", "Im the storm that is approaching", QTime::currentTime().toString("hh:mm:ss"), "", ""}};

    ConversationCell *convCell = new ConversationCell(this);
    convCell->setData(convCells);
    ui->widget_4->layout()->addWidget(convCell);

    connect(convCell, &ConversationCell::cellDoubleClicked_signal, this, &MainWindow::cellDoubleClicked_slot);
}

void MainWindow::createChatWidget(QString name)
{
    // TODO: query database and transmit true data
    //  chat widget
    QVector<ItemInfo> myInfos = {
        {"Show case1", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"), ":/resource/head/3.bmp", "lets go and play basket ball", Unit::Right, Unit::Text},
        {"Show case1", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"), ":/resource/head/3.bmp", "lets go and play basket ball", Unit::Right, Unit::Text},
        {"Show case1", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"), ":/resource/head/3.bmp", "lets go and play basket ball", Unit::Right, Unit::Text},
        {"Show case1", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"), ":/resource/head/3.bmp", "lets go and play basket ball", Unit::Right, Unit::Text},
        {"Show case1", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"), ":/resource/head/6.bmp", "why not, playint basket ball is gonna be marvelous, lets go", Unit::Left, Unit::Text},
        {"Show case1", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"), ":/resource/head/6.bmp", "why not, playint basket ball is gonna be marvelous, lets go", Unit::Left, Unit::Text},
        {"Show case1", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"), ":/resource/head/6.bmp", "why not, playint basket ball is gonna be marvelous, lets go", Unit::Left, Unit::Text},
        {"Show case1", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"), ":/resource/head/6.bmp", "why not, playint basket ball is gonna be marvelous, lets go", Unit::Left, Unit::Text},
        {"Show case1", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"), ":/resource/head/6.bmp", "why not, playint basket ball is gonna be marvelous, lets go", Unit::Left, Unit::Text}};

    if (m_chatWidget->isHidden())
    {
        ChatWidget *chat = new ChatWidget;
        chat->setData(myInfos);
        chat->scrollToBottom();
        chat->show();
    }
    else
    {
        ChatWidget *chat = new ChatWidget(m_chatWidget);
        chat->setData(myInfos);
        m_chatWidget->layout()->addWidget(chat);
        chat->scrollToBottom();
    }
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
            m_direction = Unit::ResizeDirection::Left;
        else
            m_direction = Unit::ResizeDirection::Right;
    }
    else if (onVerticalEdge(e->pos()))
    {
        if (e->pos().y() - rect().top() < 15)
            m_direction = Unit::ResizeDirection::Top;
        else
            m_direction = Unit::ResizeDirection::Bottom;
    }
    else
        m_direction = Unit::ResizeDirection::None;
    CustomMoveWidget::mousePressEvent(e);
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    // widget resize or move
    // TODO: 缩放到一定大小chatWidget显示或消失
    if (m_mousePressed)
    {
        QPoint delta = e->pos() - mousePoint;
        switch (m_direction)
        {
        case Unit::ResizeDirection::Left:
            if (width() == minimumWidth() && delta.x() > 0)
                break;
            setGeometry(x() + delta.x(), y(), width() - delta.x(), height());
            setCursor(Qt::SizeHorCursor);
            break;
        case Unit::ResizeDirection::Right:
            setGeometry(x(), y(), width() + delta.x(), height());
            mousePoint = e->pos();
            setCursor(Qt::SizeHorCursor);
            break;
        case Unit::ResizeDirection::Top:
            if (height() == minimumHeight() && delta.y() > 0)
                break;
            setGeometry(x(), y() + delta.y(), width(), height() - delta.y());
            setCursor(Qt::SizeVerCursor);
            break;
        case Unit::ResizeDirection::Bottom:
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

void MainWindow::conv_btn_clicked(bool check)
{
    stackedWidgetChanged(0);
}

void MainWindow::contact_btn_clicked(bool check)
{
    if (ui->contact_btn->isChecked())
        return;
    stackedWidgetChanged(1);
}

void MainWindow::btnGrp_toggled(QAbstractButton *btn, bool check)
{
    if (check)
        return;
    if (btn == ui->conv_btn)
    {
        stackedWidgetChanged(Unit::Conversation);
    }
    else if (btn == ui->contact_btn)
    {
        stackedWidgetChanged(Unit::Contact);
    }
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

void MainWindow::cellDoubleClicked_slot(QString name)
{
    qDebug() << "received signal" << name;
    createChatWidget(name);
}
