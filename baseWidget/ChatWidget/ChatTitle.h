#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class ChatTitle;
}
QT_END_NAMESPACE

class ChatTitle : public QWidget
{
    Q_OBJECT
public:
    ChatTitle(QWidget *parent = 0);
    ~ChatTitle();

    void setPartnerName(const QString &name);

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    void initUI();

private:
    void nameBtn_clicked_slot();
    void dialAudioBtn_clicked_slot();
    void dialVideoBtn_clicked_slot();
    void moreBtn_clicked_slot();

private:
    Ui::ChatTitle *ui;
};