#include "user_list.h"

User_List *User_List::_instance = new User_List();

User_List::~User_List()
{
    map<int,User *>::iterator it;
    for(it = user_list.begin();it != user_list.end();++it)
    {
        delete it->second;
    }
}

void User_List::add_uer(User *user)
{
    user_list[user->user_id] = user;
}

void User_List::remove_user(int user_id)
{
    iterator it = user_list.find(user_id);
    user_list.erase(it);
}

User_List::user_list_t User_List::get_user_list()
{
    return user_list;
}

User_List *::User_List::getInstance()
{
    return _instance;
}

User_List::iterator User_List::list_begin()
{
    return user_list.begin();
}

User_List::iterator User_List::list_end()
{
    return user_list.end();
}

User *User_List::getUser(int user_id)
{
    iterator it = user_list.find(user_id);
    if(it == user_list.end())
        return NULL;
    return it->second;
}
