#ifndef HANDLE_BASE_H
#define HANDLE_BASE_H
#include "msg.h"
#include "../user_list.h"
#include "../uimanage.h"

class Handle_Base{
    public:
        virtual ~Handle_Base(){}
        virtual void handle_msg(struct Msg *msg) = 0;
};

#endif // HANDLE_BASE_H
