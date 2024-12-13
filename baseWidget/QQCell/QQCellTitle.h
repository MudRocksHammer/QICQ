#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QEvent>
#include <QHBoxLayout>

class QQCellTitle : public QWidget
{
    Q_OBJECT
public:
    QQCellTitle(QWidget *parent = 0);

    void setCount(const int &online, const int &total);
    void setName(const QString &name);

protected:
    void paintEvent(QPaintEvent *e) override;
    bool eventFilter(QObject *obj, QEvent *e) override;

private:
    void initUI();
    void updateUI();

signals:
    void titleClicked_signal(bool);

private:
    QLabel *m_arrow_label;
    QLabel *m_name_label;
    QLabel *m_count_label;

    QString m_name;

    int m_online;
    int m_total;
    bool m_isOpen;
    bool m_isHover;
};