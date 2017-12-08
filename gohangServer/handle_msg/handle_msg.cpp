#include "user_list.h"
#include "handle_list.h"

#include "../log.h"

//初始化
void handle_init()
{
    //初始化操作列表
    HandleList::getInstance()->init();
}

//处理消息
void handle_msg(struct bufferevent *bev,struct Msg *msg)
{
    Handle_Base *base = HandleList::getInstance()->getHandle(msg->protocol);
    
    if(base != NULL)
    {
        base->handle_msg(bev,msg);
    }
}


//销毁所有
void free_handle()
{
    delete User_List::getInstance();
    delete HandleList::getInstance();
}


//移除客户端
void remove_client(int user_id)
{
    printf("user id = %d\n",user_id);
    User_List::getInstance()->remove_user(user_id);
}
