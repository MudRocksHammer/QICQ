#ifndef __CLIENTSOCKET_H__
#define __CLIENTSOCKED_H__

#include <QObject>
#include <QTcpSocket>
#include <QFile>

class ClientSocket : public QObject{
    Q_OBJECT
public:
    explicit ClientSocket(QObject* parent = 0);
    ~ClientSocket();

    quint64 getUserID() const;
    void setUserID(const quint64& ID);

    void checkConnect();
    void closeConnect();

    //连接服务器
    void connectToHost(const QString& host, const int& port);
    void connectToHost(const QHostAddress& host, const int port);

private:
    //解析登录返回信息
    void parseLogin(const QJsonValue& dataVal);
    //解析注册返回信息
    void parseRegister(const QJsonValue& dataVal);

signals:
    void message_signal(const quint8& type, const QJsonValue& dataValue);
    void status_signal(const quint8& state);

public slots:
    //socket消息发送封装
    void sendMessge_slot(const quint8& type, const QJsonValue& dataVal);
    //发送上线通知
    void sendOnLine_slot();
    //下线
    void sendOffLine_slot();

private slots:
    //与服务器断开连接
    void disconnect_slot();
    //与服务器发起连接
    void connect_slot();
    //tcp消息处理
    void readyRead_slot();

private:
    QTcpSocket* m_tcpSocket;
    quint64 m_nId;

};

class ClientFileSocket : public QObject{
    Q_OBJECT
public:
    explicit ClientFileSocket(QObject* parent = 0);
    ~ClientFileSocket();

    bool isConnected();

    //发送文件大小等信息
    void startTransferFile(QString fileReadName);

    //连接到服务器
    void connectToServer(const QString& host, const int& port, const quint64& userID);
    //断开服务器
    void closeConnect();

    //文件传输完成
    void fileTransFinished();

    //设置当前socket的id
    void setUserId(const quint64& id);

private:
    //socket 初始化
    void initSocket();

signals:
    void sendFinished_signal();
    void fileRecvOk_signal(const quint8& type, const QString& filePath);
    void updateProgress(quint64 curSize, quint64 total);
    void connected_signal();

public slots:

private slots:
    //显示错误
    void displayError(QAbstractSocket::SocketError);
    //发送文件数据。更新进度条
    void updateClientProgress_slot(quint64);

    //文件接收
    void readyRead_slot();
    void connected_slot();
    void disconnect_slot();

private:
    quint64 loadSize;       //每次发送数据大小

    ///--------------------------------ReceiveFile------------------------------
    quint64 byteReceived;           //已经接收的信息大小
    quint64 fileNameSize;           //文件名大小
    QString fileReadName;           //存放文件名
    QByteArray inBlock;             //数据缓冲区
    quint64 recvTotalBytes;         //接收数据总大小
    QFile* fileToRecv;              //接收的文件

    ///-------------------------------SendFile-----------------------------------
    quint16 blockSize;              //存放发送文件的信息大小
    QFile* fuleToSend;              //要发送的文件
    quint64 sendTotalBytes;         //发送数据总大小
    quint64 bytesWritten;           //已经发送的数据大小
    quint64 bytesToWritel;          //剩余发送数据大小
    QByteArray outBlock;            //数据缓冲区，即存放每次要发送的数据

    //用户目录
    QString m_strFilePath;

    //通信类
    QTcpSocket* m_tcpSock;
    bool m_busy;
    quint64 m_nWinId;
    quint8 m_nType;
};

#endif