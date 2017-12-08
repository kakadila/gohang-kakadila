#ifndef CONNECT_HANDLE_H
#define CONNECT_HANDLE_H

#include "../handle_base.h"
#include "../handle_list.h"

#include <string.h>
#include <QDebug>


//处理登录返回
class connect_handle : public Handle_Base
{
public:
    virtual void handle_msg(Msg *msg)
    {
        qDebug()<<"连接成功";
        //显示登录界面
        UIManage::getInstance()->connect_widget->close();
        UIManage::getInstance()->login_widget->show();
    }
};

#endif // CONNECT_HANDLE_H
