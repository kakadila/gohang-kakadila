#ifndef __UPDATE_USER_LIST_H_
#define __UPDATE_USER_LIST_H_

#include "../handle_base.h"
#include "../handle_list.h"

#include <string.h>
#include <stdio.h>
#include "../../log.h"

class update_userlist_handle:public Handle_Base
{
    virtual void handle_msg(struct bufferevent *bev,struct Msg *msg)
    {
        int size;
        User *user;
        User_List::iterator it;
//        printf("map count = %d\n",User_List::getInstance()->get_user_list().size());
        for(it = User_List::getInstance()->list_begin();
                it != User_List::getInstance()->list_end();
                ++it)
        {
           user = it->second;
           size = user->name.size();
           sendMsg(bev,PROTOCOL_USER_INFO,user->user_id,size);
           bufferevent_write(bev,user->name.c_str(),size);
        }

        //最后发送个回应包，表示所有用户都发送完成
        sendMsg(bev,PROTOCOL_UPDATE_USERLIST,0,0);
    }
};

#endif
