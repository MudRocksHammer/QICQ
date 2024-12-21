/********************************************************************************
** Form generated from reading UI file 'ChatInput.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATINPUT_H
#define UI_CHATINPUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatInput
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *emoji_btn;
    QPushButton *cutScreen_btn;
    QPushButton *file_btn;
    QPushButton *picture_btn;
    QPushButton *audioMsg_btn;
    QSpacerItem *horizontalSpacer;
    QPushButton *history_btn;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *send_btn;

    void setupUi(QWidget *ChatInput)
    {
        if (ChatInput->objectName().isEmpty())
            ChatInput->setObjectName(QString::fromUtf8("ChatInput"));
        ChatInput->resize(717, 200);
        ChatInput->setMaximumSize(QSize(16777215, 200));
        verticalLayout = new QVBoxLayout(ChatInput);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        emoji_btn = new QPushButton(ChatInput);
        emoji_btn->setObjectName(QString::fromUtf8("emoji_btn"));

        horizontalLayout->addWidget(emoji_btn);

        cutScreen_btn = new QPushButton(ChatInput);
        cutScreen_btn->setObjectName(QString::fromUtf8("cutScreen_btn"));

        horizontalLayout->addWidget(cutScreen_btn);

        file_btn = new QPushButton(ChatInput);
        file_btn->setObjectName(QString::fromUtf8("file_btn"));

        horizontalLayout->addWidget(file_btn);

        picture_btn = new QPushButton(ChatInput);
        picture_btn->setObjectName(QString::fromUtf8("picture_btn"));

        horizontalLayout->addWidget(picture_btn);

        audioMsg_btn = new QPushButton(ChatInput);
        audioMsg_btn->setObjectName(QString::fromUtf8("audioMsg_btn"));

        horizontalLayout->addWidget(audioMsg_btn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        history_btn = new QPushButton(ChatInput);
        history_btn->setObjectName(QString::fromUtf8("history_btn"));

        horizontalLayout->addWidget(history_btn);


        verticalLayout->addLayout(horizontalLayout);

        textEdit = new QTextEdit(ChatInput);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setMaximumSize(QSize(16777215, 100));

        verticalLayout->addWidget(textEdit);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        send_btn = new QPushButton(ChatInput);
        send_btn->setObjectName(QString::fromUtf8("send_btn"));

        horizontalLayout_2->addWidget(send_btn);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(ChatInput);

        QMetaObject::connectSlotsByName(ChatInput);
    } // setupUi

    void retranslateUi(QWidget *ChatInput)
    {
        ChatInput->setWindowTitle(QCoreApplication::translate("ChatInput", "ChatInput", nullptr));
        emoji_btn->setText(QString());
        cutScreen_btn->setText(QString());
        file_btn->setText(QString());
        picture_btn->setText(QString());
        audioMsg_btn->setText(QString());
        history_btn->setText(QString());
        send_btn->setText(QCoreApplication::translate("ChatInput", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatInput: public Ui_ChatInput {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATINPUT_H
