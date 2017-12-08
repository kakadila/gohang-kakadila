#ifndef WELCOME_HANDLE_H
#define WELCOME_HANDLE_H
#include "../handle_base.h"
#include "../handle_list.h"

#include <string.h>
#include <QDebug>
#include <QMessageBox>


//处理登录返回
class welcome_handle : public Handle_Base
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


        char buf[20] = {0};
        QTcpSocket *socket = TcpSocketHelper::getInstance()->getSocket();
        socket->read(buf,sizeof(buf));

        User *user = User_List::getInstance()->get_user(msg->sender);
        QString user_name = user->name.c_str();
        QString mainrole_name = User_List::getInstance()->get_main_role()->name.c_str();

        if(strcmp(buf,"black")==0)
        {
            UIManage::getInstance()->gohang_widget->init(true,mainrole_name,user_name,black,user->user_id);
            UIManage::getInstance()->gohang_widget->show();
        }else if(strcmp(buf,"white")==0)
        {
            UIManage::getInstance()->gohang_widget->init(true,user_name,mainrole_name,white,user->user_id);
            UIManage::getInstance()->gohang_widget->show();
        }else if(strcmp(buf,"welcome")==0)
        {
             int ret =QMessageBox::information(NULL, "error", "对方邀请你对战，是否接受?", QMessageBox::Ok, QMessageBox::Cancel);
             char retbuf[1024] = {0};
             if(ret == QMessageBox::Ok)
             {
                 strcpy(retbuf,"black"); //对方的棋子颜色
                 TcpSocketHelper::getInstance()->sendMsg(PROTOCOL_WELCOME,user->user_id,strlen(retbuf));
                 socket->write(retbuf,strlen(retbuf));

                 UIManage::getInstance()->gohang_widget->init(true,user_name,mainrole_name,white,user->user_id);
                 UIManage::getInstance()->gohang_widget->show();
             }else
             {
                 strcpy(retbuf,"cancel"); //拒绝对方
                 TcpSocketHelper::getInstance()->sendMsg(PROTOCOL_WELCOME,user->user_id,strlen(retbuf));
                 socket->write(retbuf,strlen(retbuf));
             }
        }else if(strcmp(buf,"cancel")==0)
        {
            QMessageBox::information(NULL, "error", "对方拒绝了你", QMessageBox::Yes, QMessageBox::No);
            return;
        }
    }
};

#endif // WELCOME_HANDLE_H
