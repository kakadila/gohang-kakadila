#include "handle_list.h"

#include "../protocol.h"
#include "msg_option/login_handle.h"
#include "msg_option/connect_handle.h"
#include "msg_option/user_info_handle.h"
#include "msg_option/update_userlist_handle.h"
#include "msg_option/register_user_handle.h"
#include "msg_option/welcome_handle.h"
#include "msg_option/dropdown_handle.h"

HandleList *HandleList::_instance = new HandleList();

//初始化
void HandleList::init()
{
    option_list[PROTOCOL_LOGIN] = new login_handle();  //登录处理
    option_list[PROTOCOL_CONNECT] = new connect_handle();  //连接成功处理
    option_list[PROTOCOL_USER_INFO] = new user_info_handle();  //用户信息处理
    option_list[PROTOCOL_UPDATE_USERLIST] = new update_userlist_handle();  //用户更新
    option_list[PROTOCOL_REGISTER] = new register_user_handle();  //用户注册
    option_list[PROTOCOL_WELCOME] = new welcome_handle();  //用户邀请
    option_list[PROTOCOL_DROPDOWM] = new dropdown_handle();  //落子信息
}


HandleList::HandleList()
{
    this->init();
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
    return option_list[protocol];
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


