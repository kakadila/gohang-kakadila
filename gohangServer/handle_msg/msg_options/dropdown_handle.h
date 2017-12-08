#ifndef __DROPDOWN_HANDLE_H_
#define __DROPDOWN_HANDLE_H_ 

#include "../handle_base.h"
#include "../handle_list.h"
#include "../sql_handle.h"

#include <string.h>
#include <stdio.h>
#include "../../log.h"

class dropdown_handle:public Handle_Base
{
    virtual void handle_msg(struct bufferevent *bev,struct Msg *msg)
    {
        uint32_t to_id = msg->sender;
        User *to_user = User_List::getInstance()->getUser(to_id);
        char buf[20] = {0};
        bufferevent_read(bev,buf,msg->len);

        printf("user_id= %d,buf=%s\n",to_id,buf);

        if(to_user == NULL)
        {
            //这个用户已经退出
            sendMsg(bev,PROTOCOL_DROPDOWN,0,0);
            return;
        }

        //发送给要传达的人
        struct bufferevent *to_bev = to_user->bev;
        sendMsg(to_bev,PROTOCOL_DROPDOWN,msg->owner_id,strlen(buf));
        bufferevent_write(to_bev,buf,strlen(buf));

    }
};

#endif
