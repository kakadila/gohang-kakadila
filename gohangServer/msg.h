#ifndef __MSG_H_
#define __MSG_H_

#include <event2/bufferevent.h>
#include <event2/buffer.h>

#include "protocol.h"

struct Msg
{
   uint32_t len;
   uint32_t protocol;
   uint32_t sender;

   //这个值在用户登录后赋值，不能修改
   uint32_t owner_id;
};

void sendMsg(struct bufferevent *bev,uint32_t protocol,uint32_t sender,uint32_t data_len);

void send_msg(struct bufferevent *,struct Msg *);

#endif
