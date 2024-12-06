#ifndef CLIENTEDIT_H
#define CLIENTEDIT_H

#include <QLineEdit>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QRegExp>
#include <QRegExpValidator>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>

#define IP_INPUT_SIZE 4

class IPEdit : public QLineEdit{
    Q_OBJECT
public:
    explicit IPEdit(QWidget* parent = 0);
    ~IPEdit();

    QString text();

protected:
    void keyPressEvent(QKeyEvent* e) override;
    bool eventFilter(QObject* obj, QEvent* e) override;
    void mouseDoubleClickEvent(QMouseEvent* e) override;

private slots:
    void selectAll();
    void clearAll();
    void mouseSelect_slot(QPoint pos);
    void textChanged_slot(int index, int input);

private:
    QLineEdit* m_lineEdit[IP_INPUT_SIZE];
    bool isAllSelected;
    bool isMousePressing;
    QPoint mouseStartPos;
};

class IconEdit : public QLineEdit{
    Q_OBJECT
public:
    explicit IconEdit(QWidget* parent = 0);
    ~IconEdit() {}

    void setIcon(const QString& url);
    void enableClear(bool);

private slots:
    void textChanged_slot(const QString& text);
    void clear_btn_clicked_slot();

private:
    QLabel* icon_label;
    QPushButton* clear_btn;
    bool isIconShow;
    bool isClearShow;
};

#endif // CLIENTEDIT_H
