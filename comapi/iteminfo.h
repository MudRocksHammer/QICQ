#ifndef ITEMINFO_H
#define ITEMINFO_H

#include <QtCore/qglobal.h>
#include <QPixmap>
#include <QRectF>
#include "unit.h"

class ItemInfo
{
public:
    ItemInfo();
    ItemInfo(const QString& strName, const QString& datetime, const QString& pixmap
             , const QString& text, const QString& strSize
             , const quint8& orientation = Right, const quint8& msgType = Text);

    ~ItemInfo();

public:
    void setName(const QString& text);
    QString getName() const;

    void setDatetime(const QString& text);
    QString getDatetime() const;

    void setHeadPixmap(const QString& pixmap);
    QString getPixmap() const;

    void setText(const QString& text);
    QString getText() const;

    void setFileSizeString(const QString& strSize);
    QString getFileSizeString() const;

    void setOrientation(const quint8& orientation);
    quint8 getOrientation() const;

    void setMsgType(const quint8& msgType);
    quint8 getMsgType() const;

    void setItemHeight(qreal itemHeight);
    qreal getItemHeight() const;

    void setBubbleRect(const QRectF& bubbleRect);
    QRectF getBubbleRect() const;

private:
    //消息标题 名字、时间等
    QString m_strName;
    //消息日期
    QString m_strDatetime;
    //头像图片
    QString m_strPixmap;
    //消息内容
    QString m_strText;
    //如果是文件，显示文件大小
    QString m_strSize;
    //气泡方向
    quint8 m_orient;
    //消息类型
    quint8 m_msgType;
    //height 暂时没有用
    qreal m_itemHeight;
    //气泡方框坐标
    QRectF m_bubbleRect;
    //消息状态
    quint8 m_nStatus;
};

#endif // ITEMINFO_H
