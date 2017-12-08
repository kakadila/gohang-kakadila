#ifndef USER_INFO_HANDLE_H
#define USER_INFO_HANDLE_H

#include "../handle_base.h"
#include "../handle_list.h"

#include <string.h>
#include <QDebug>


//处理登录返回
class user_info_handle : public Handle_Base
{
public:
    virtual void handle_msg(Msg *msg)
    {
         User *user = new User();
         char buf[msg->len+1] = {0};
         QTcpSocket *socket = TcpSocketHelper::getInstance()->getSocket();
         socket->read(buf,msg->len);

        // qDebug()<<msg->sender;
         //qDebug()<<buf;
         //将用户信息加入用户列表
         user->user_id = msg->sender;
         user->name = buf;

         User_List::getInstance()->add_uer(user);

    }
};
#endif // USER_INFO_HANDLE_H
