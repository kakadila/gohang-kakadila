#ifndef __READ_CB_H_
#define __READ_CB_H_


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <event2/bufferevent.h>
#include "handle_msg/handle_msg.h"

void conn_readcb(struct bufferevent *bev,void *user_data);

void conn_eventcb(struct bufferevent *, short, void *);

#endif
