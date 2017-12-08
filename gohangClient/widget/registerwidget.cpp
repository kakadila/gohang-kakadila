#include "registerwidget.h"
#include "ui_registerwidget.h"
#include <QString>
#include <QMessageBox>
#include <string.h>
#include "tcpsockethelper.h"

RegisterWidget::RegisterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterWidget)
{
    ui->setupUi(this);
}

RegisterWidget::~RegisterWidget()
{
    delete ui;
}

void RegisterWidget::on_pushButton_clicked()
{
    QTcpSocket *socket = TcpSocketHelper::getInstance()->getSocket();

    QString username = ui->le_username->text();
    QString password1 = ui->le_psword1->text();
    QString password2 = ui->le_psword2->text();

    if(username.isNull() || password1.isNull())
    {
         QMessageBox::information(NULL, "error", "用户名或密码不能为空", QMessageBox::Yes, QMessageBox::No);
        return;
    }

    if(username.size() > 18)
    {
         QMessageBox::information(NULL, "error", "用户名太长", QMessageBox::Yes, QMessageBox::No);
         return;
    }

    if(password1.size() > 24)
    {
         QMessageBox::information(NULL, "error", "密码太长", QMessageBox::Yes, QMessageBox::No);
         return;
    }

    if(password1.compare(password2)!= 0)
    {
         QMessageBox::information(NULL, "error", "两次输入密码不一样", QMessageBox::Yes, QMessageBox::No);
         return;
    }

    char buf[1024] = {0};
    sprintf(buf,"username=%s&&password=%s",
            username.toStdString().c_str(),
            password1.toStdString().c_str());

    //发送数据
    TcpSocketHelper::getInstance()->sendMsg(PROTOCOL_REGISTER,0,strlen(buf));
    socket->write(buf,strlen(buf));

}
