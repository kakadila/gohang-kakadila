#ifndef __LOGIN_HANDLE_H_
#define __LOGIN_HANDLE_H_

#include "../handle_base.h"
#include "../handle_list.h"
#include "../sql_handle.h"

#include <string.h>
#include <stdio.h>
#include "../../log.h"

class login_handle:public Handle_Base
{
    virtual void handle_msg(struct bufferevent *bev,struct Msg *msg)
    {

        printf("len = %d\n",msg->len);

        //空消息
        if(msg->len == 0)
        {
            return;
        }

        char buf[1024] = {0};
        bufferevent_read(bev,buf,msg->len);

        //解析用户名和密码
        char *name = strtok(buf,"&&");
        char *password = strtok(NULL,"=");
        password = strtok(NULL,"\0");

        name = strtok(name,"=");
        name = strtok(NULL,"\0");

        printf("name = %s,password = %s\n",name,password);
                //将用户名和密码与数据库比较
        User *tmp_user = Sql_Handle::getInstance()->get_user(name);
        if(tmp_user == NULL)
        {
            sendMsg(bev,msg->protocol,0,0);
            return;
        }
        if(User_List::getInstance()->getUser(tmp_user->user_id)!=NULL)
        {
            sendMsg(bev,msg->protocol,0,0);
            return;
        }


        User *user = new User();
        user->name = name;
        user->pass_word = password;

        user->bev = bev;
        user->user_id = tmp_user->user_id;
        //将这个用户保存到用户列表
        User_List::getInstance()->add_uer(user);

        //代表这个用户的消息结构体赋值
        msg->owner_id = user->user_id;

        sendMsg(bev,msg->protocol,user->user_id,0);

        delete tmp_user;
    }
};

#endif
