#ifndef TCTSOCKETHELPER_H
#define TCTSOCKETHELPER_H

#include <QString>
#include <QTcpSocket>

#include "msg.h"

class TcpSocketHelper: public QObject
{
    Q_OBJECT
public:
    TcpSocketHelper();
    ~TcpSocketHelper();

    static TcpSocketHelper *getInstance();
    static void init();
    static void release(){delete _instance;}

    //获取socket
    QTcpSocket *getSocket();

    //读一个消息
    void readMsg(Msg &msg);

    void sendMsg(uint32_t protocol, uint32_t sender, uint32_t data_len);

private slots:

    void readcb();

private:
    static TcpSocketHelper *_instance;

    QTcpSocket *socket;

};

#endif // TCTSOCKETHELPER_H
