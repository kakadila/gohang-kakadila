
#include <QApplication>
#include "uimanage.h"
#include "tcpsockethelper.h"

static void init();
static void release();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //初始化
    init();

    int ret = a.exec();

    //释放
    release();

    return ret;
}

static void init()
{
    TcpSocketHelper::init();
    UIManage::init();
    UIManage::getInstance()->connect_widget->show();

}

static void release()
{
    UIManage::release();
    TcpSocketHelper::release();
}
