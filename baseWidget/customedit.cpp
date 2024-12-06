#include "customedit.h"

IPEdit::IPEdit(QWidget *parent) : QLineEdit(parent), isMousePressing(false), isAllSelected(false)
{
    QHBoxLayout *hlayout = new QHBoxLayout(this);
    hlayout->setContentsMargins(1, 1, 1, 1);
    hlayout->setSpacing(0);

    QRegExp regx("(25[0-5]|2[0-4][0-9]|1?[0-9]{1,2})");

    for (int i = 0; i < IP_INPUT_SIZE; ++i)
    {
        m_lineEdit[i] = new QLineEdit(this);

        // 去除边框
        m_lineEdit[i]->setFrame(false);

        // 输入框最大位数
        m_lineEdit[i]->setMaxLength(3);

        // 保存小部件默认布局
        m_lineEdit[i]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        m_lineEdit[i]->setAlignment(Qt::AlignRight);

        //正则表达式匹配输入
        m_lineEdit[i]->setValidator(new QRegExpValidator(regx));

        m_lineEdit[i]->installEventFilter(this);
        //connect(m_lineEdit[i], &QLineEdit::insertAction, this, &

       // m_lineEdit[i]->setFixedWidth(width);
        hlayout->addWidget(m_lineEdit[i]);

        if (i < 3)
        {
            QLabel *dot = new QLabel(this);
            dot->setText(".");
            dot->setFixedWidth(2);
            dot->setStyleSheet("QLabel{ color: black; }");
            hlayout->addWidget(dot);
        }
    }
    // this->setReadOnly(true);

    m_lineEdit[0]->setFocus();
    m_lineEdit[0]->selectAll();
}

IPEdit::~IPEdit()
{
}

QString IPEdit::text()
{
    QString str;
    for(int i = 0; i < IP_INPUT_SIZE; ++i){
            str += m_lineEdit[i]->text();
            if(i != 3)
                str += ".";
    }
    return str;
}

void IPEdit::keyPressEvent(QKeyEvent *e)
{
    QWidget::keyPressEvent(e);
    qDebug() << "enter key pressed event" << e->key();
    if(e->key() == Qt::Key_Period){
        qDebug() << "Period pressed";
    }
    if(e->key() == Qt::Key_Left){
        qDebug() << "Left btn pressed";
    }
}

bool IPEdit::eventFilter(QObject *obj, QEvent *e)
{
    //键盘事件
    if(e->type() == QEvent::KeyPress){
        QKeyEvent* key_e = static_cast<QKeyEvent*>(e);
        if(key_e->modifiers() == Qt::ControlModifier && key_e->key() == Qt::Key_A){
            selectAll();
            return true;
        }
        //当前Edit
        for(int i = 0; i < IP_INPUT_SIZE; ++i){
            if(obj == m_lineEdit[i]){
                //捕获事件
                if(key_e->key() == Qt::Key_Backspace){
                    if(isAllSelected){
                        clearAll();
                        return true;
                    }
                    //如果当前输入框为空，转到前一个
                    if(m_lineEdit[i]->text().isEmpty() && i > 0){
                        m_lineEdit[i - 1]->setFocus();
                        m_lineEdit[i - 1]->end(false);
                        return true;
                    }
                }
                if(key_e->key() == Qt::Key_Left){
                    if(m_lineEdit[i]->cursorPosition() == 0 && i > 0){
                        m_lineEdit[i - 1]->setFocus();
                        m_lineEdit[i - 1]->end(false);
                        return true;
                    }
                }
                if(key_e->key() == Qt::Key_Right){
                    if(m_lineEdit[i]->cursorPosition() == m_lineEdit[i]->text().size() && i < IP_INPUT_SIZE - 1){
                        m_lineEdit[i + 1]->setFocus();
                        m_lineEdit[i + 1]->home(false);
                        return true;
                    }
                }
                if(key_e->key() == Qt::Key_Period){
                    if(i < IP_INPUT_SIZE - 1){
                        m_lineEdit[i + 1]->setFocus();
                        m_lineEdit[i + 1]->home(false);
                        return true;
                    }
                }
                if(key_e->key() >= Qt::Key_0 && key_e->key() <= Qt::Key_9){
                    textChanged_slot(i, key_e->key() - 0x30);
                    
                }
                
                return false;
            }
        }
    }

    //鼠标单击事件
    if(e->type() == QEvent::MouseButtonPress){
        isMousePressing = true;
        mouseStartPos = static_cast<QMouseEvent*>(e)->globalPos();
        //qDebug() << mouseStartPos;
        //qDebug() << m_lineEdit[0]->cursorPositionAt(mouseStartPos - m_lineEdit[0]->mapToGlobal(QPoint(1, 1)));
    }

    //鼠标双击事件
    if(e->type() == QEvent::MouseButtonDblClick){
        mouseDoubleClickEvent(static_cast<QMouseEvent*>(e));
    }

    //鼠标移动事件
    if(e->type() == QEvent::MouseMove){
        //if(isMousePressing)
            //mouseSelect_slot(static_cast<QMouseEvent*>(e)->globalPos());
    }

    //鼠标release事件
    if(e->type() == QEvent::MouseButtonRelease){
        isMousePressing = false;
    }
    return false;
}

void IPEdit::mouseDoubleClickEvent(QMouseEvent *e)
{
    selectAll();
    
    e->accept();
}

void IPEdit::clearAll()
{
    for(int i = 0; i < IP_INPUT_SIZE; ++i){
        if(m_lineEdit[i]->hasSelectedText()){
            QString text = m_lineEdit[i]->text();
            text.remove(m_lineEdit[i]->selectionStart(), m_lineEdit[i]->selectionLength());
            m_lineEdit[i]->clear();
            m_lineEdit[i]->setText(text);
        }
    }
    isAllSelected = false;
}

void IPEdit::mouseSelect_slot(QPoint pos)
{
    for(int i = 0; i < IP_INPUT_SIZE; ++i){
        int start = m_lineEdit[i]->cursorPositionAt(mouseStartPos);
        int cur = m_lineEdit[i]->cursorPositionAt(pos);
        int len = cur - start;
        m_lineEdit[i]->setSelection(start, len);
        m_lineEdit[i]->setCursorPosition(cur);
    }
}

void IPEdit::textChanged_slot(int index, int input)
{
    QLineEdit* edit = m_lineEdit[index];
    QString text = edit->text();

    if((text.length() == 3 || m_lineEdit[index]->text().toInt() * 10 > 255) && index < IP_INPUT_SIZE - 1){
        m_lineEdit[index + 1]->setFocus();
        m_lineEdit[index + 1]->home(false);
        m_lineEdit[index + 1]->setText(QString::number(input));
    }
}

void IPEdit::selectAll(){
    for(int i = 0; i < 4; ++i){
        m_lineEdit[i]->selectAll();
    }
    isAllSelected = true;
}

IconEdit::IconEdit(QWidget* parent) : QLineEdit(parent), isIconShow(false){
    icon_label = new QLabel(this);
    icon_label->setFixedSize(16, 16);
    icon_label->setVisible(false);
    icon_label->setCursor(Qt::ArrowCursor);

    clear_btn = new QPushButton(this);
    clear_btn->setMinimumSize(16, 16);
    clear_btn->setStyleSheet("QPushButton{ \
        background-color: rgb(64, 64, 64); \
        background-image: url(:/resource/common/clear.png); \
        background-repeat: no-repeat; \
        background-position: center; \
        width: 16px; \
        height: 16px; \
    }");
    clear_btn->setVisible(false);
    clear_btn->setCursor(Qt::PointingHandCursor);

    connect(this, &QLineEdit::textChanged, this, &IconEdit::textChanged_slot);
    connect(clear_btn, &QPushButton::clicked, this, &IconEdit::clear_btn_clicked_slot);
}

void IconEdit::setIcon(const QString &url)
{
    QPixmap pix(url);
    icon_label->setPixmap(pix);
    icon_label->setGeometry(2, (this->height() - pix.height()) / 2, pix.width(), pix.width());
    icon_label->setVisible(true);
    this->setTextMargins(25, 1, 1, 1);
    isIconShow = true;
}

void IconEdit::enableClear(bool enable)
{      
    if(enable){
        clear_btn->setGeometry(this->width() - 20, (this->height() - 16) / 2, 16, 16);
        clear_btn->setVisible(true);
        if(isIconShow)
            this->setTextMargins(25, 1, 25, 1);
        else
            this->setTextMargins(1, 1, 25, 1);
    }
    else{
        clear_btn->setVisible(enable);
        if(isIconShow)
            this->setTextMargins(25, 1, 1, 1);
        else
            this->setTextMargins(1, 1, 1, 1);
    }
}

void IconEdit::clear_btn_clicked_slot()
{
    this->setText("");
    setFocus();
}

void IconEdit::textChanged_slot(const QString& text){
    if(!text.isEmpty()){
        enableClear(true);
    }
    else{
        enableClear(false);
    }
}
