#ifndef LOGIN_HANDLE_H
#define LOGIN_HANDLE_H

#include "../handle_base.h"
#include "../handle_list.h"

#include <string.h>
#include <QDebug>
#include <QMessageBox>


//处理登录返回
class login_handle : public Handle_Base
{
public:
    virtual void handle_msg(Msg *msg)
    {
        if(msg->sender == 0)
        {
            QMessageBox::information(NULL, "error", "用户名或密码错误", QMessageBox::Yes, QMessageBox::No);
            return;
        }
       qDebug()<<"登录成功";
      //  qDebug()<<msg->sender;

        User *user = User_List::getInstance()->get_main_role();
        user->user_id = msg->sender;

        //显示登录界面
        UIManage::getInstance()->login_widget->close();
        UIManage::getInstance()->hall_widget->show();
        UIManage::getInstance()->hall_widget->showUpdate();
    }
};

#endif // LOGIN_HANDLE_H
