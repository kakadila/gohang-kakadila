#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QString>
#include <string.h>
#include "msg_handle/handle_msg.h"
#include "user_list.h"
#include <QMessageBox>
#include "uimanage.h"


LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    this->socket = TcpSocketHelper::getInstance()->getSocket();

}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_btn_login_clicked()
{
    QString name = ui->le_username->text();
    QString password = ui->le_password->text();

    if(name.isEmpty() || password.isEmpty())
    {
        QMessageBox::information(NULL, "error", "用户名或密码不能为空", QMessageBox::Yes, QMessageBox::No);
        return;
    }

    char buf[1024] = {0};
    sprintf(buf,"username=%s&&password=%s",
            name.toStdString().c_str(),
            password.toStdString().c_str());

    //设置用户名
    User_List::getInstance()->get_main_role()->name = name.toStdString();

    //发送数据
    TcpSocketHelper::getInstance()->sendMsg(PROTOCOL_LOGIN,0,strlen(buf));
    this->socket->write(buf,strlen(buf));

}

void LoginWidget::on_btn_register_clicked()
{
    UIManage::getInstance()->register_widget->show();
}
