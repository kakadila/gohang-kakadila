#include "handle_msg.h"
#include "user_list.h"
#include "handle_list.h"
#include "handle_base.h"


void Handle_Msg::handle_msg(Msg *msg)
{
    Handle_Base *base = HandleList::getInstance()->getHandle(msg->protocol);

       if(base != NULL)
       {
           base->handle_msg(msg);
       }
}

void Handle_Msg::remove_client(int user_id)
{
    User_List::getInstance()->remove_user(user_id);

}
