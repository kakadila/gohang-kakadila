#ifndef USER_LIST_H
#define USER_LIST_H


#include <string>
#include <QMap>
#include <QDebug>
using namespace std;

struct User
{
    int user_id;
    string name;
};

class User_List
{
public:
    typedef QMap<int,User *>::iterator iterator;
    typedef QMap<int,User *> user_list_t;
public:
        User_List();
        ~User_List();

        User *get_main_role();
        User *get_user(uint32_t user_id);
        void add_uer(User *user);
        void remove_user(int user_id);
        user_list_t get_user_list();
        void clead_all();

        iterator list_begin();
        iterator list_end();

        static User_List *getInstance();

    private:
        user_list_t user_list;
        static User_List *_instance;
        User main_role;
};


#endif // USER_LIST_H
