#include "sql_handle.h"

#define DATABASE_NAME "my_gohangHall"
#define DATABASE_USER "root"
#define DATABASE_PASSWORD "123456"
#define HOST_NAME "localhost"

Sql_Handle *Sql_Handle::_instance = new Sql_Handle();

Sql_Handle::Sql_Handle()
{
    //当需要多线程的时候再处理
    //在query的时候如果不加锁可能会出问题
    m_lock = NULL;

    mysql = mysql_init(NULL);
    if(mysql == NULL)
    {
        mysql_error(mysql);
        exit(-1);
    }

    if(mysql_real_connect(mysql,HOST_NAME,DATABASE_USER,
                DATABASE_PASSWORD,
                DATABASE_NAME,
                0,NULL,0) == NULL)
    {
        mysql_error(mysql);
        exit(-1);
    }
}

void Sql_Handle::save_user(User *user)
{
    char buf[1024] = {0};
    sprintf(buf,(char *)"insert into userdata(name,password) values('%s','%s')",user->name.c_str(),user->pass_word.c_str());
    
    //密码使用完成之后置空
    user->pass_word = "";
    query(buf,false);
}

User *Sql_Handle::get_user(int user_id)
{
    char buf[1024] = {0};
    sprintf(buf,(char *)"select uid,name,password from userdata where uid = %d",user_id);
    
    MYSQL_RES *res = query(buf,true);
    if(res == NULL)
    {
        printf("query error\n");
        return NULL;
    }

    
    MYSQL_ROW row = mysql_fetch_row(res);
    if(row == NULL)
    {
        return NULL;
    }


    User *user = new User();
    user->user_id = atoi(row[0]);
    user->name = row[1];
    user->pass_word = row[2];

    mysql_free_result(res);

    return user;
}

User *Sql_Handle::get_user(char *name)
{
    char buf[1024] = {0};
    sprintf(buf,(char *)"select uid,name,password from userdata where name = '%s'",name);
    
    MYSQL_RES *res = this->query(buf,true);
    if(res == NULL)
    {
        printf("query error\n");
        return NULL;
    }

    
    MYSQL_ROW row = mysql_fetch_row(res);
    if(row == NULL)
    {
        return NULL;
    }

    User *user = new User();
    user->user_id = atoi(row[0]);
    user->name = row[1];
    user->pass_word = row[2];
//    printf("name=%s,password=%s\n",user->name.c_str(),user->pass_word.c_str());
    mysql_free_result(res);

    return user;
}

//执行语句
MYSQL_RES *Sql_Handle::query(char *str,bool is_select)
{
    lock();
    if(mysql_query(mysql,str)!=0)
    {
        printf("query error :%s \n",str);
        mysql_error(mysql);
        unlock();
        return NULL;
    }
    unlock();

    if(is_select)
    {
        MYSQL_RES *res = mysql_store_result(mysql);
        return res;
    }
    return NULL;
}

Sql_Handle::~Sql_Handle()
{
    this->destroy_lock();
    mysql_close(mysql);
}

//加锁和解锁
void Sql_Handle::lock()
{

}

void Sql_Handle::unlock()
{
}

void Sql_Handle::destroy_lock()
{
}


