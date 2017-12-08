#ifndef HANDLE_LIST_H
#define HANDLE_LIST_H

#include "handle_msg.h"
#include "handle_base.h"
#include <map>

using namespace std;

class HandleList
{
    public:
        HandleList();
        ~HandleList();

        //获取消息处理
        Handle_Base *getHandle(int protocol);

        //注册消息处理
        void register_handle(int protocol,Handle_Base *base);

        //获取实例
        static HandleList *getInstance();

        //初始化
        void init();

    private:
        map<int,Handle_Base *> option_list;

        static HandleList *_instance;
};

#endif // HANDLE_LIST_H
