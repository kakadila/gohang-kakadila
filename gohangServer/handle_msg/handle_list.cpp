#include "handle_list.h"

#include "../log.h"
#include "../protocol.h"
#include "msg_options/login_handle.h"
#include "msg_options/update_userlist_handle.h"
#include "msg_options/register_handle.h"
#include "msg_options/welcome_handle.h"
#include "msg_options/dropdown_handle.h"

HandleList *HandleList::_instance = new HandleList();

HandleList::HandleList()
{
}

HandleList::~HandleList()
{
    map<int,Handle_Base *>::iterator it;
    for(it = option_list.begin();it!=option_list.end();++it)
    {
        delete it->second;
    }

}

//获取消息处理
Handle_Base *HandleList::getHandle(int protocol)
{
    iterator it = option_list.find(protocol);
    if(it == option_list.end())
        return NULL;
    return it->second;
}
//注册消息处理
void HandleList::register_handle(int protocol,Handle_Base *base)
{
    option_list[protocol] = base;
}

//获取实例
HandleList *HandleList::getInstance()
{
    return _instance;
}


//初始化
void HandleList::init()
{
    option_list[PROTOCOL_LOGIN] = new login_handle(); //登录处理
    option_list[PROTOCOL_UPDATE_USERLIST] = new update_userlist_handle(); //更新处理
    option_list[RPROTOCOL_REGISTER] = new myregister_handle(); //注册处理
    option_list[PROTOCOL_WELCOME] = new welcome_handle(); //注册处理
    option_list[PROTOCOL_DROPDOWN] = new dropdown_handle(); //落子处理
}
