#include "conn_cb.h"
#include <event2/util.h>
#include <event2/event.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include "msg.h"
#include <stdio.h>

static void read_head(struct bufferevent *bev,void *user_data);

//读取身体
static void read_body(struct bufferevent *bev,void *user_data)
{
    struct Msg *msg= (struct Msg *)user_data;

    bufferevent_read(bev,&msg->protocol,sizeof(msg->protocol));
    msg->protocol = ntohl(msg->protocol);
    printf("protocol = %d\n",msg->protocol);

    bufferevent_read(bev,&msg->sender,sizeof(msg->protocol));
    msg->sender = ntohl(msg->sender);
    printf("sender= %d\n",msg->sender);

    msg->len -= 2 * sizeof(uint32_t);
    printf("-------------------------\n");

    //处理消息
    handle_msg(bev,msg);

    //获取长度
    struct evbuffer *input = bufferevent_get_input(bev);
    int len = evbuffer_get_length(input);

    if(len >= sizeof(msg->len))
    {
        read_head(bev,(void *)msg);
    }else
    {
        bufferevent_setwatermark(bev,EV_READ,sizeof(msg->len),0);
        bufferevent_setcb(bev,read_head,NULL,conn_eventcb,(void *)msg);
    }

}

//读取消息头
static void read_head(struct bufferevent *bev,void *user_data)
{  
    struct Msg *msg = (struct Msg *)user_data;

    bufferevent_read(bev,&msg->len,sizeof(msg->len));

    msg->len = ntohl(msg->len);
    printf("msg len = %d\n",msg->len);

    //获取长度
    struct evbuffer *input = bufferevent_get_input(bev);
    int len = evbuffer_get_length(input);

    if(len >= msg->len)
    {
        read_body(bev,(void *)msg);
    }else
    {
        bufferevent_setwatermark(bev,EV_READ,msg->len,0);
        bufferevent_setcb(bev,read_body,NULL,conn_eventcb,(void *)msg);
    }
}

void conn_readcb(struct bufferevent *bev,void *user_data)
{
    struct Msg *msg = (struct Msg *)malloc(sizeof(struct Msg)); 
    memset(msg,0,sizeof(struct Msg));

    read_head(bev,(void *)msg);
}

    void
conn_eventcb(struct bufferevent *bev, short events, void *user_data)
{
    if (events & BEV_EVENT_EOF) {
        printf("Connection closed.\n");
    } else if (events & BEV_EVENT_ERROR) {
        printf("Got an error on the connection: %s\n",
                strerror(errno));/*XXX win32*/
    }

    //将客户端从队列中移除
    if(user_data != NULL)
    {
        struct Msg *msg = (struct Msg *)user_data;
        remove_client(msg->owner_id);

        //将msg结构体释放
        if(msg !=NULL)
            free(msg);
    }

    /* None of the other events can happen here, since we haven't enabled
     * timeouts */
    bufferevent_free(bev);
}


