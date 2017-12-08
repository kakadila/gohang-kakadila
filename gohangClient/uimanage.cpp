#include "uimanage.h"

UIManage *UIManage::_instance = NULL;
UIManage::UIManage()
{
    this->connect_widget = new Widget();
    this->login_widget = new LoginWidget();
    this->hall_widget = new HallWidget();
    this->register_widget = new RegisterWidget();
    this->gohang_widget = new GoHangWidget();
}

UIManage *UIManage::getInstance()
{
    return UIManage::_instance;
}

void UIManage::init()
{
     UIManage::_instance = new UIManage();
}
