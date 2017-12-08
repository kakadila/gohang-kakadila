#ifndef __WELCOM_HANDLE_H_
#define __WELCOM_HANDLE_H_ 

#include "../handle_base.h"
#include "../handle_list.h"
#include "../sql_handle.h"

#include <string.h>
#include <stdio.h>
#include "../../log.h"

class welcome_handle:public Handle_Base
{
    virtual void handle_msg(struct bufferevent *bev,struct Msg *msg)
    {
        uint32_t to_id = msg->sender;
        User *to_user = User_List::getInstance()->getUser(to_id);
        char buf[20] = {0};
        bufferevent_read(bev,buf,msg->len);
        printf("to_id = %d,buf = %s\n",to_id,buf);

        if(to_user == NULL)
        {
            //这个用户已经退出
            sendMsg(bev,PROTOCOL_WELCOME,0,0);
            return;
        }

        struct bufferevent *to_bev = to_user->bev;
        User *user = User_List::getInstance()->getUser(msg->owner_id);
    int size = user->name.size();
    sendMsg(to_bev,PROTOCOL_USER_INFO,user->user_id,size);
    bufferevent_write(to_bev,user->name.c_str(),size);



        //发送给要传达的人
        sendMsg(to_bev,PROTOCOL_WELCOME,msg->owner_id,strlen(buf));
        bufferevent_write(to_bev,buf,strlen(buf));

    }
};

#endif
