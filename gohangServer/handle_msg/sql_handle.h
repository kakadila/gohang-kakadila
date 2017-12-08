#ifndef __SQL_HANDLE_H_
#define __SQL_HANDLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "user_list.h"

class Sql_Handle
{
    public:
        Sql_Handle();
        ~Sql_Handle();

        //保存用户
        void save_user(User *user);
        
        //获取用户
        User *get_user(int user_id);
        User *get_user(char *name);

        static Sql_Handle *getInstance(){return _instance;}

    private:
        MYSQL_RES *query(char *str,bool is_select = false);

        void lock();
        void unlock();
        void destroy_lock();
    private:
        MYSQL *mysql;

        void *m_lock;
        static Sql_Handle *_instance;
};


#endif
