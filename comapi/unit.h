#ifndef UNIT_H
#define UNIT_H

#include <QString>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <stdint.h>

namespace Unit
{

#define MY_VERSION 0x01000001
#define MY_VERSION_STR "1.0.0.1"

// 版本检测
#define VERSION_CHECK(a, b, c, d) ((a << 24) | (b << 16) | (c << 8) | d)

#define MSG_PORT_ONLINE 6353
#define MSG_PORT_MESSAGE 5363
#define TCP_FILE_PORT 7777

// Ip Messenger Communication Protocol version 1.0 define
#define GET_MODE(command) (command & 0x000000ffUL)
#define GET_OPT(command) (command & 0xffffff00UL)

// header
#define IPMSG_VERSION 0x0001
#define IPMSG_DEFAULT_PORT 0x0979

// command
#define IPMSG_NOOPERATION 0x00000000  // 不操作
#define IPMSG_BR_ENTRY 0x00000001     // 用户上线
#define IPMSG_BR_EXIT 0x00000002      // 用户退出
#define IPMSG_NOTIFY_ENTRY 0x00000003 // 通报在线
#define IPMSG_BR_ABSENCE 0x00000004   // 隐身
#define IPMSG_REGISTER 0x00000005     // 注册

#define IPMSG_BR_ISGETLIST 0x00000010
#define IPMSG_OKGETLIST 0x00000011 //
#define IPMSG_GETLIST 0x00000012
#define IPMSG_ANS_LIST 0x00000013
#define IPMSG_FILE_MTIME 0x00000014
#define IPMSG_FILE_ANSWER 0x00000015
#define IPMSG_FILE_CREATETIME 0x00000016
#define IPMSG_BR_ISGETLIST2 0x00000017

#define IPMSG_SENDMSG 0x00000020 // 发送消息
#define IPMSG_RECVMSG 0x000021   // 通报接收消息

#define IPMSG_READMSG 0x00000030 // 用户读取消息
#define IPMSG_DELMSG 0x00000031  // 撤销消息

// option for all command
#define IPMSG_ABSENCE_OPT 0x00000100
#define IPMSG_SERVEROPT 0x00000200
#define IPMSG_DIAL_UP_OPT 0x00010000
#define IPMSG_FILEATTACHOPT 0x00200000

// file types for fileattach command
#define IPMSG_FILE_REGULAR 0x00000001UL
#define IPMSG_FILE_DIR 0x00000002UL
#define IPMSG_LISTGET_TIMER 0x0104
#define IPMSG_LISTGETRETRY_TIMER 0x0105

// 聊天气泡相关设置
#define ITEM_START_ANGLE 270
#define ITEM_D_ANGLE 2
#define ITEM_D_ZOOMING_FACTOR 0.05
#define UPDATE_TIMER_INTERVAL 10
#define ITEM_COUNTER_TIMER_INTERVAL 200
#define SIZE_HINT QSize(300, 300)

#define ITEM_HEIGHT 80
#define ITEM_FONT_SIZE 18
#define ITEM_HEAD_SIZE 40
#define BG_START_COLOR QColor(179, 179, 183)
#define BG_END_COLOR QColor(187, 193, 207)

#define ITEM_START_COLOR ITEM_END_COLOR.lighter()
#define ITEM_END_COLOR QColor(62, 135, 166)

#define ITEM_START_COLOR_A ITEM_END_COLOR_A.lighter()
#define ITEM_END_COLOR_A QColor(221, 221, 221)

#define HOVER_OPACITY 0.2
#define HOVER_START_COLOR HOVER_END_COLOR.lighter()
#define HOVER_END_COLOR QColor(98, 139, 21)

#define HOVER_TEXT_COLOR Qt::red
#define SELECT_TEXT_COLOR Qt::white
#define NORMAL_TEXT_COLOR Qt::black

#define RECV_RADIUS 4

#define ITEM_SPACE 20
#define ITEM_TITLE_HEIGHT 20

    typedef enum
    {
        None,
        Left,
        Right
    } Orientation;

    typedef enum
    {
        Text,
        Audio,
        Picture,
        Files
    } MessageType;

    typedef enum
    {
        Uknown,
        Register = 0x10,
        Login,
        Logout,
        LoginRepeat,

        UserOnLine = 0x15,
        UserOffLine,
        UpdateHeadPic,

        AddFriend = 0x20,
        AddGroup,

        AddFriendRequest,
        AddGroupRequest,

        CreateGroup = 0x25,

        GetMyFriends = 0x30,
        GetMyGroups,

        RefreshFriends = 0x35,
        RefreshGroups,

        SendMsg = 0x40,
        SendGroupMsg,
        SendFile,
        SendPicture,
        SendFace,

        ChangePasswd = 0x50,

        DeleteFriend = 0x55,
        DeleteGroup,

        SendFileOk = 0x60,

        GetFile = 0x65,
        GetPicture
    } E_MSG_TYPE;

    typedef enum
    {
        ConnectedHost = 0x01,
        DisconnectedHost,

        LoginSuccess,
        LoginPasswdError,

        OnLine,
        OffLine,

        RegisterOk,
        RegisterFailed,

        AddFriendOk,
        AddFriendFailed
    } E_STATUS;

    enum class ResizeDirection
    {
        Left,
        Right,
        Top,
        Bottom,
        None
    };

    enum MiddleArea
    {
        Contact,
        Conversation,
        Group
    };
}

#endif // UNIT_H