/********************************************************************************
** Form generated from reading UI file 'ChatWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWIDGET_H
#define UI_CHATWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *return_btn;
    QPushButton *mini_btn;
    QPushButton *max_btn;
    QPushButton *close_btn;

    void setupUi(QWidget *ChatWidget)
    {
        if (ChatWidget->objectName().isEmpty())
            ChatWidget->setObjectName(QString::fromUtf8("ChatWidget"));
        ChatWidget->resize(544, 291);
        ChatWidget->setMinimumSize(QSize(300, 0));
        verticalLayout = new QVBoxLayout(ChatWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 6, 6, -1);
        widget = new QWidget(ChatWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(390, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        return_btn = new QPushButton(widget);
        return_btn->setObjectName(QString::fromUtf8("return_btn"));
        return_btn->setMaximumSize(QSize(30, 20));

        horizontalLayout->addWidget(return_btn);

        mini_btn = new QPushButton(widget);
        mini_btn->setObjectName(QString::fromUtf8("mini_btn"));
        mini_btn->setMaximumSize(QSize(30, 20));

        horizontalLayout->addWidget(mini_btn);

        max_btn = new QPushButton(widget);
        max_btn->setObjectName(QString::fromUtf8("max_btn"));
        max_btn->setMaximumSize(QSize(30, 20));

        horizontalLayout->addWidget(max_btn);

        close_btn = new QPushButton(widget);
        close_btn->setObjectName(QString::fromUtf8("close_btn"));
        close_btn->setMaximumSize(QSize(30, 20));

        horizontalLayout->addWidget(close_btn);


        horizontalLayout_2->addWidget(widget);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(ChatWidget);

        QMetaObject::connectSlotsByName(ChatWidget);
    } // setupUi

    void retranslateUi(QWidget *ChatWidget)
    {
        ChatWidget->setWindowTitle(QCoreApplication::translate("ChatWidget", "ChatWidget", nullptr));
        return_btn->setText(QString());
        mini_btn->setText(QString());
        max_btn->setText(QString());
        close_btn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ChatWidget: public Ui_ChatWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWIDGET_H
