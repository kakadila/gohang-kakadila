#ifndef __HANDLE_BASE_H_
#define __HANDLE_BASE_H_

#include <event2/bufferevent.h>
#include "../msg.h"
#include "user_list.h"

class Handle_Base{
    public:
        virtual ~Handle_Base(){}
        virtual void handle_msg(struct bufferevent *bev,struct Msg *msg) = 0;
};

#endif
