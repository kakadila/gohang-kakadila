#ifndef HANDLE_MSG_H
#define HANDLE_MSG_H

#include "msg.h"

class Handle_Msg
{
public:
    static void handle_msg(Msg *msg);

    static void remove_client(int user_id);
};

#endif // HANDLE_MSG_H
