#include "hallwidget.h"
#include "ui_hallwidget.h"
#include <QDebug>
#include <QBrush>

#include "user_list.h"
#include "tcpsockethelper.h"
#include "uimanage.h"

HallWidget::HallWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HallWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("五子棋对战平台");
}



HallWidget::~HallWidget()
{
    delete ui;
}


void HallWidget::showUpdate()
{
    QString name = QString(User_List::getInstance()->get_main_role()->name.c_str());
    ui->lb_main_role->setText(name);

    //先清空所有
    ui->lw_userlist->clearAllItem();

    //遍历所有用户
    User_List::iterator it;
    for(it = User_List::getInstance()->list_begin();
        it !=  User_List::getInstance()->list_end();++it)
    {
        ListItem *item = ui->lw_userlist->getItem();
        item->user_id = it.value()->user_id;
       // item->setIcon(QIcon(QPixmap(":/Image/face.png")));
        item->setText(QString(it.value()->name.c_str()));
        item->setTextAlignment(Qt::AlignLeft|Qt::AlignCenter);
        item->setFont(QFont("楷体",12));
        item->setBackgroundColor(QColor(134,244,123));
        ui->lw_userlist->addItem(item);
    }

}


void HallWidget::on_btn_update_clicked()
{
    User_List::getInstance()->clead_all();
    TcpSocketHelper::getInstance()->sendMsg(PROTOCOL_UPDATE_USERLIST,
                                            User_List::getInstance()->get_main_role()->user_id,
                                         0);
}

void HallWidget::on_pushButton_clicked()
{
    //单机游戏
    QString black_name = User_List::getInstance()->get_main_role()->name.c_str();
    QString white_name = "电脑";
    UIManage::getInstance()->gohang_widget->init(false,black_name,white_name);
    UIManage::getInstance()->gohang_widget->show();
}
