#ifndef UPDATE_USERLIST_HANDLE_H
#define UPDATE_USERLIST_HANDLE_H

#include "../handle_base.h"
#include "../handle_list.h"

#include <string.h>
#include <QDebug>

//更新用户列表
class update_userlist_handle : public Handle_Base
{
public:
    virtual void handle_msg(Msg *msg)
    {
        //更新在线用户
       // qDebug()<<"更新在线用户";
        UIManage::getInstance()->hall_widget->showUpdate();
    }
};

#endif // UPDATE_USERLIST_HANDLE_H
