#include "user_list.h"

User_List *User_List::_instance = new User_List();

User_List::User_List()
{
    this->main_role.user_id = 0;
}

User_List::~User_List()
{
    iterator it;
    for(it = user_list.begin();it != user_list.end();++it)
    {
        delete it.value();
    }
}

User *User_List::get_main_role()
{
    return &this->main_role;
}

User *User_List::get_user(uint32_t user_id)
{
     if(!user_list.contains(user_id))
     {
        return NULL;
     }
     return user_list[user_id];
}

void User_List::add_uer(User *user)
{
    if(user_list.contains(user->user_id)
            ||main_role.user_id == user->user_id)
    {
        return;
    }
    user_list[user->user_id] = user;
}

void User_List::remove_user(int user_id)
{
   user_list.remove(user_id);
}
User_List::user_list_t User_List::get_user_list()
{
    return user_list;
}

void User_List::clead_all()
{
    user_list.clear();
}

User_List::iterator User_List::list_begin()
{
    return user_list.begin();
}

User_List::iterator User_List::list_end()
{
    return user_list.end();
}

User_List *::User_List::getInstance()
{
    return _instance;
}
