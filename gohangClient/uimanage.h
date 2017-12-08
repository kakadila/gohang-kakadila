#ifndef UIMANAGE_H
#define UIMANAGE_H

#include "widget/widget.h"
#include "widget/loginwidget.h"
#include "widget/hallwidget.h"
#include "widget/registerwidget.h"
#include "widget/gohangwidget.h"
class UIManage
{
public:
    UIManage();

    static UIManage* getInstance();
    static void init();
    static void release(){delete _instance;}

private:
    static UIManage *_instance;

public:
    Widget *connect_widget; //连接界面
    LoginWidget *login_widget;  //登录界面
    HallWidget *hall_widget;  //大厅界面
    RegisterWidget *register_widget; //注册界面
    GoHangWidget *gohang_widget; //五子棋界面
};

#endif // UIMANAGE_H
