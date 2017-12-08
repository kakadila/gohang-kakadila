#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include <QDebug>
#include "tcpsockethelper.h"
#include "uimanage.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //初始化socket
    socket = TcpSocketHelper::getInstance()->getSocket();

    //显示连接
    ui->wg_connect->setHidden(false);


}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btn_login_clicked()
{
    QString ip = ui->le_ip->text();
    quint16 port = ui->le_port->text().toUInt();
    socket->connectToHost(ip,port);
}



//void Widget::on_pushButton_2_clicked()
//{
//    socket->disconnectFromHost();
//    socket->destroyed();
//}
