#ifndef DROPDOWN_HANDLE_H
#define DROPDOWN_HANDLE_H
#include "../handle_base.h"
#include "../handle_list.h"

#include <string.h>
#include <QDebug>
#include <QMessageBox>


//处理登录返回
class dropdown_handle : public Handle_Base
{
public:
    virtual void handle_msg(Msg *msg)
    {
        //0表示对方已经下线
        if(msg->sender == 0)
        {
            QMessageBox::information(NULL, "error", "对方已下线", QMessageBox::Yes, QMessageBox::No);
            return;
        }

        char buf[msg->len] = {0};
        QTcpSocket *socket = TcpSocketHelper::getInstance()->getSocket();
        socket->read(buf,msg->len);

        int x,y;
        sscanf(buf,"%d,%d",&x,&y);

        UIManage::getInstance()->gohang_widget->other_dropDown(x,y);
    }
};
#endif // DROPDOWN_HANDLE_H
