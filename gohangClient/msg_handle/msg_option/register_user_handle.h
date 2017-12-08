#ifndef REGISTER_USER_HANDLE_H
#define REGISTER_USER_HANDLE_H
#include "../handle_base.h"
#include "../handle_list.h"

#include <string.h>
#include <QDebug>
#include <QMessageBox>


//处理登录返回
class register_user_handle : public Handle_Base
{
public:
    virtual void handle_msg(Msg *msg)
    {
        if(msg->sender == 0)
        {
            QMessageBox::information(NULL, "error", "用户名已经存在", QMessageBox::Yes, QMessageBox::No);
            return;
        }
        QMessageBox::information(NULL, "error", "注册成功", QMessageBox::Yes, QMessageBox::No);


        //关闭注册界面
        UIManage::getInstance()->register_widget->close();
    }
};

#endif // REGISTER_HANDLE_H
