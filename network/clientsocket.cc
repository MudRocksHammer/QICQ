#include "clientsocket.h"
#include "unit.h"
#include "myapp.h"
//#include "databasemanager.h"

#include <QDebug>
#include <QDataStream>
#include <QApplication>

ClientSocket::ClientSocket(QObject* parent) 
                : QObject(parent), m_nId(0), m_tcpSocket(new QTcpSocket(this)){
    connect(m_tcpSocket, &QTcpSocket::readyRead, this, &ClientSocket::readyRead_slot);
    connect(m_tcpSocket, &QTcpSocket::connected, this, &ClientSocket::connect_slot);
    connect(m_tcpSocket, &QTcpSocket::disconnected, this, &ClientSocket::disconnect_slot);
}

ClientSocket::~ClientSocket(){
    sendOffLine_slot();
}

quint64 ClientSocket::getUserID () const{
    return m_nId;
}

void ClientSocket::setUserID(const quint64 &ID)
{
    m_nId = ID;
}

void ClientSocket::checkConnect()
{
    if(m_tcpSocket->state() != QTcpSocket::ConnectedState)
        m_tcpSocket->connectToHost(MyApp::m_strHostAddr, MyApp::m_nMsgPort);
}

void ClientSocket::closeConnect(){
    if(m_tcpSocket->isOpen()) m_tcpSocket->abort();
}

void ClientSocket::connectToHost(const QString &host, const int &port)
{
    if(m_tcpSocket->isOpen()) m_tcpSocket->abort();
    m_tcpSocket->connectToHost(host, port);
}

void ClientSocket::connectToHost(const QHostAddress &host, const int port)
{
    if(m_tcpSocket->isOpen()) m_tcpSocket->abort();
    m_tcpSocket->connectToHost(host, port);
}

void ClientSocket::parseLogin(const QJsonValue &dataVal)
{
    if(dataVal.isObject()){
        QJsonObject dataObj = dataVal.toObject();
        int code = dataObj.value("code").toInt();
        QString msg = dataObj.value("msg").toString();
        QString strHead = dataObj.value("head").toString();

        if(code == 0 && msg == "ok"){
            m_nId = dataObj.value("id").toString().toULongLong();
            //保存头像
            MyApp::m_strHeadFile = MyApp::m_strHeadPath + strHead;

            MyApp::m_nId = m_nId;
            Q_EMIT status_signal(LoginSuccess);
        }
        else if(code == -1){
            Q_EMIT status_signal(LoginPasswdError);
        }
        else if(code == -1){
            Q_EMIT status_signal(LoginRepeat);
        }
    }
}

void ClientSocket::parseRegister(const QJsonValue &dataVal)
{
    if(dataVal.isObject()){
        QJsonObject dataObj = dataVal.toObject();
        m_nId = dataObj.value("id").toInt();

        if(m_nId == 0){
            Q_EMIT status_signal(RegisterFailed);
        }
        else{
            Q_EMIT status_signal(RegisterOk);
        }
    }
}

void ClientSocket::sendOnLine_slot()
{
    // 上线的时候给当前好友上报下状态
    //QJsonArray friendArr = DataBaseManager::getInstance()->getMyFriend(MyApp::m_nId);
    // 组织Jsonarror
    //SltSendMessage(UserOnLine, friendArr);
}

void ClientSocket::sendOffLine_slot()
{
    QJsonObject json;
    json.insert("id", QString::number(m_nId));
    //QJsonObject friendArr = DataBaseManager::getInstance()->getMyFriend(MyApp:m_nId);
    //json.insert("friends", friendArr);

    //通知下线
    this->sendMessge_slot(Logout, json);
}

void ClientSocket::connect_slot()
{
    qDebug() << "has connected";
    Q_EMIT status_signal(ConnectedHost);
}

void ClientSocket::readyRead_slot()
{
    //读取socket数据
    QByteArray byRead = m_tcpSocket->readAll();
    QJsonParseError jsonError;
    //转化为json文档
    QJsonDocument document = QJsonDocument::fromJson(byRead, &jsonError);

    //解析成功
    if(!document.isNull() && (jsonError.error == QJsonParseError::NoError)){
        //JSON文档为对象
        if(document.isObject()){
            //转化为对象
            QJsonObject jsonObj = document.object();
            QJsonValue dataVal = jsonObj.value("data");

            int nType = jsonObj.value("type").toInt();

            //根据消息类型解析服务器消息
            switch (nType)
            {
            case Register:
                parseRegister(dataVal);
                break;
            case Login:
                parseLogin(dataVal);
                break;
            case UserOnLine:
                qDebug() << "user is online" << dataVal;
                Q_EMIT message_signal(UserOnLine, dataVal);
                break;
            case UserOffLine:
                qDebug() << "user is offline" << dataVal;
                Q_EMIT message_signal(UserOffLine, dataVal);
                break;
            case Logout:
                m_tcpSocket->abort();
                break;
            case UpdateHeadPic:
                Q_EMIT message_signal(UpdateHeadPic, dataVal);
                break;
            case AddFriend:
                Q_EMIT message_signal(AddFriend, dataVal);
                break;
            case AddGroup:
                Q_EMIT message_signal(AddGroup, dataVal);
                break;
            case AddFriendRequest:
                Q_EMIT message_signal(AddFriendRequest, dataVal);
                break;
            case AddGroupRequest:
                Q_EMIT message_signal(AddGroupRequest, dataVal);
                break;
            case CreateGroup:
                Q_EMIT message_signal(CreateGroup, dataVal);
                break;
            case GetMyFriends:
                Q_EMIT message_signal(GetMyFriends, dataVal);
                break;
            case GetMyGroups:
                Q_EMIT message_signal(GetMyGroups, dataVal);
                break;
            case RefreshFriends:
                Q_EMIT message_signal(RefreshFriends, dataVal);
                break;
            case RefreshGroups:
                Q_EMIT message_signal(RefreshGroups, dataVal);
                break;
            case SendMsg:
                Q_EMIT message_signal(SendMsg, dataVal);
                break;
            case SendGroupMsg:
                Q_EMIT message_signal(SendGroupMsg, dataVal);
                break;
            case SendFile:
                Q_EMIT message_signal(SendFile, dataVal);
                break;
            case SendPicture:
                Q_EMIT message_signal(SendPicture, dataVal);
                break;
            default:
                break;
            }
        }
    }
}

void ClientSocket::sendMessge_slot(const quint8& type, const QJsonValue& dataVal){
    //连接服务器
    if(!m_tcpSocket->isOpen()){
        m_tcpSocket->connectToHost(MyApp::m_strHostAddr, MyApp::m_nMsgPort);
        m_tcpSocket->waitForConnected(1000);
    }
    //连接服务器超时
    if(!m_tcpSocket->isOpen()) return;

    //构建json对象
    QJsonObject json;
    json.insert("type", type);
    json.insert("from", QString::number(m_nId));
    json.insert("data", dataVal);

    //构建json文档
    QJsonDocument document;
    document.setObject(json);
    m_tcpSocket->write(document.toJson(QJsonDocument::Compact));
}

void ClientSocket::disconnect_slot(){
    qDebug() << "has disconnected";
    Q_EMIT status_signal(ConnectedHost);
}