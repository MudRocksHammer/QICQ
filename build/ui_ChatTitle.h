/********************************************************************************
** Form generated from reading UI file 'ChatTitle.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATTITLE_H
#define UI_CHATTITLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatTitle
{
public:
    QHBoxLayout *horizontalLayout;
    QPushButton *userName_btn;
    QSpacerItem *horizontalSpacer;
    QPushButton *dialAudio_btn;
    QPushButton *dialVideo_btn;
    QPushButton *shareScreen_btn;
    QPushButton *moreChat_btn;

    void setupUi(QWidget *ChatTitle)
    {
        if (ChatTitle->objectName().isEmpty())
            ChatTitle->setObjectName(QString::fromUtf8("ChatTitle"));
        ChatTitle->resize(646, 300);
        horizontalLayout = new QHBoxLayout(ChatTitle);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        userName_btn = new QPushButton(ChatTitle);
        userName_btn->setObjectName(QString::fromUtf8("userName_btn"));

        horizontalLayout->addWidget(userName_btn);

        horizontalSpacer = new QSpacerItem(50, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        dialAudio_btn = new QPushButton(ChatTitle);
        dialAudio_btn->setObjectName(QString::fromUtf8("dialAudio_btn"));

        horizontalLayout->addWidget(dialAudio_btn);

        dialVideo_btn = new QPushButton(ChatTitle);
        dialVideo_btn->setObjectName(QString::fromUtf8("dialVideo_btn"));

        horizontalLayout->addWidget(dialVideo_btn);

        shareScreen_btn = new QPushButton(ChatTitle);
        shareScreen_btn->setObjectName(QString::fromUtf8("shareScreen_btn"));

        horizontalLayout->addWidget(shareScreen_btn);

        moreChat_btn = new QPushButton(ChatTitle);
        moreChat_btn->setObjectName(QString::fromUtf8("moreChat_btn"));

        horizontalLayout->addWidget(moreChat_btn);


        retranslateUi(ChatTitle);

        QMetaObject::connectSlotsByName(ChatTitle);
    } // setupUi

    void retranslateUi(QWidget *ChatTitle)
    {
        ChatTitle->setWindowTitle(QCoreApplication::translate("ChatTitle", "ChatTitle", nullptr));
        userName_btn->setText(QString());
        dialAudio_btn->setText(QString());
        dialVideo_btn->setText(QString());
        shareScreen_btn->setText(QString());
        moreChat_btn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ChatTitle: public Ui_ChatTitle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATTITLE_H
