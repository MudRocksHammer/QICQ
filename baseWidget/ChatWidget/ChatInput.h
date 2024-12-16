#pragma once

#include <QWidget>
#include <QFile>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class ChatInput;
}
QT_END_NAMESPACE

class ChatInput : public QWidget
{
    Q_OBJECT
public:
    ChatInput(QWidget *parent = 0);
    ~ChatInput();

private:
    void initUI();

private:
    void emojiBtn_clicked_slot();
    void cutScreenBtn_clicked_slot();
    void fileBtn_clicked_slot();
    void pictureBtn_clicked_slot();
    void audioMsgBtn_clicked_slot();
    void historyBtn_clicked_slot();
    void sendBtn_clicked_slot();

private:
    Ui::ChatInput *ui;
};