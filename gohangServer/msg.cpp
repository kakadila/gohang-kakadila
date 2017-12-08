#include "msg.h"
#include <arpa/inet.h>
#include <string.h>


void sendMsg(struct bufferevent *bev,uint32_t protocol,uint32_t sender,uint32_t data_len)
{
    struct Msg msg;
    memset(&msg,0,sizeof(msg));
    msg.protocol = protocol;
    msg.len = data_len + sizeof(msg.sender)+sizeof(msg.protocol);
    msg.sender = sender;

    send_msg(bev,&msg);
}

void send_msg(struct bufferevent *bev,struct Msg *msg)
{
    uint32_t tmp;
    tmp = htonl(msg->len);
    bufferevent_write(bev,&tmp,sizeof(tmp));

    tmp = htonl(msg->protocol);
    bufferevent_write(bev,&tmp,sizeof(tmp));

    tmp = htonl(msg->sender);
    bufferevent_write(bev,&tmp,sizeof(tmp));

   
}
