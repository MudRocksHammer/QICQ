#pragma once

#include <QString>
#include "../../comapi/unit.h"

class ItemInfo
{
public:
    enum InfoRole
    {
        UserNameRole = Qt::UserRole + 1,
        HeadRole,
        DateTimeRole,
        MessageRole,
        OrientationRole,
        MsgTypeRole
    };
    ItemInfo() : m_userName(), m_dateTime(), m_headPic(), m_message(), m_ori(), m_type() {}
    ItemInfo(const QString &user_name, const QString &date_time, const QString &headPic, const QString &message, const Unit::Orientation &ori = Unit::Right, const Unit::MessageType &type = Unit::Text)
        : m_userName(user_name), m_dateTime(date_time), m_headPic(headPic), m_message(message), m_ori(ori), m_type(type) {}

    void setUserName(const QString &name) { m_userName = name; }
    void setDateTime(const QString &date) { m_dateTime = date; }
    void setHeadPic(const QString &head) { m_headPic = head; }
    void setMessage(const QString &msg) { m_message = msg; }
    void setOrientation(const Unit::Orientation &ori) { m_ori = ori; }
    void setMsgType(const Unit::MessageType &type) { m_type = type; }

    QString getUserName() const { return m_userName; }
    QString getDateTime() const { return m_dateTime; }
    QString getHeadPic() const { return m_headPic; }
    QString getMessage() const { return m_message; }
    Unit::Orientation getOrientation() const { return m_ori; }
    Unit::MessageType getMessageType() const { return m_type; }

private:
    QString m_userName;
    QString m_dateTime;
    QString m_headPic;
    QString m_message;
    Unit::Orientation m_ori;
    Unit::MessageType m_type;
};