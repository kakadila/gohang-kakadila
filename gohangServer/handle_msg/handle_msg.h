#ifndef __HANDLE_MSG_H_
#define __HANDLE_MSG_H_


#include "../msg.h"
#include "handle_base.h"

//初始化
void handle_init();

//处理消息
void handle_msg(struct bufferevent *bev,struct Msg *msg);

//去掉编号
void remove_client(int user_id);

//销毁所有
void free_handle();


#endif
