#ifndef __REGISTER_HANDLE____H_
#define __REGISTER_HANDLE____H_

#include "../handle_base.h"
#include "../handle_list.h"
#include "../sql_handle.h"

#include <string.h>
#include <stdio.h>
#include "../../log.h"

class myregister_handle:public Handle_Base
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
        if(tmp_user != NULL)
        {
            char buf[] = "用户名已经存在";
            sendMsg(bev,msg->protocol,0,strlen(buf));
            bufferevent_write(bev,buf,strlen(buf));
            return;
        }

        User user;
        user.name = name;
        user.pass_word = password;
        
        //保存用户到数据库
        Sql_Handle::getInstance()->save_user(&user);

        //返回注册成功的信息
        sendMsg(bev,msg->protocol,1,0);

        delete tmp_user;

    }
};

#endif
