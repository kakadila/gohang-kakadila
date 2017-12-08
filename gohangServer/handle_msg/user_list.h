#ifndef __USER_STRUCT_H_
#define __USER_STRUCT_H_

#include <event2/bufferevent.h>
#include <string>
#include <map>
using namespace std;

struct User
{
    int user_id;
    string name;
    string pass_word;
    struct bufferevent *bev; 
};

#define USER_SIZE

class User_List
{
    public:
            typedef map<int,User *>::iterator iterator;
            typedef map<int,User *> user_list_t;
    public:
        ~User_List();

        void add_uer(User *user);
        void remove_user(int user_id);
        user_list_t get_user_list();
        User *getUser(int user_id);

         iterator list_begin();
         iterator list_end();

        static User_List *getInstance();

    private:
        user_list_t user_list;
        static User_List *_instance;
};

#endif
