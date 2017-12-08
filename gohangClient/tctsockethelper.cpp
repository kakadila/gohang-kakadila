#include "tcpsockethelper.h"
#include <QtEndian>
#include <string.h>
#include <QDebug>
#include "msg_handle/handle_msg.h"

TcpSocketHelper *TcpSocketHelper::_instance = NULL;

TcpSocketHelper::TcpSocketHelper()
{
    socket = new QTcpSocket(NULL);
     connect( socket,&QTcpSocket::readyRead,this,readcb);
     connect( socket,&QTcpSocket::disconnected,[=](){
             qDebug()<<"连接关闭";
     });
}

TcpSocketHelper::~TcpSocketHelper()
{
    TcpSocketHelper::socket->close();
   // TcpSocketHelper::socket->destroyed();
}

TcpSocketHelper *TcpSocketHelper::getInstance()
{
    return _instance;
}

void TcpSocketHelper::init()
{
    _instance = new TcpSocketHelper();
}

QTcpSocket *TcpSocketHelper::getSocket()
{
    return this->socket;
}

void TcpSocketHelper::readMsg(Msg &msg)
{
    char buf[4] = {0};
     memset((char *)&msg,0,sizeof(msg));

    socket->read(buf,sizeof(uint32_t));
    msg.len = qFromBigEndian<uint32_t>(buf);

    socket->read(buf,sizeof(uint32_t));
    msg.protocol = qFromBigEndian<uint32_t>(buf);

    socket->read(buf,sizeof(uint32_t));
    msg.sender = qFromBigEndian<uint32_t>(buf);

    msg.len -= 2 * sizeof(uint32_t);
}

void TcpSocketHelper::sendMsg(uint32_t protocol, uint32_t sender, uint32_t data_len)
{

  uint32_t len = sizeof(uint32_t) * 2+data_len;

  uint32_t tmp;

  tmp = qToBigEndian(len);
  socket->write((char *)&tmp,sizeof(tmp));

  tmp = qToBigEndian(protocol);
  socket->write((char *)&tmp,sizeof(tmp));

  tmp = qToBigEndian(sender);
  socket->write((char *)&tmp,sizeof(tmp));
}

void TcpSocketHelper::readcb()
{
    Msg msg;
    //如果还有消息继续处理
    QTcpSocket *socket = TcpSocketHelper::getInstance()->getSocket();
    while(socket->bytesAvailable()>0)
    {
        TcpSocketHelper::getInstance()->readMsg(msg);
        Handle_Msg::handle_msg(&msg);
    }
}
