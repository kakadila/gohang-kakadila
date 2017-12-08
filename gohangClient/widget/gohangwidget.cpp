#include "gohangwidget.h"
#include "ui_gohangwidget.h"

#include "tcpsockethelper.h"
#include <string.h>
#include <QMessageBox>

GoHangWidget::GoHangWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GoHangWidget)
{
    ui->setupUi(this);

    this->resize(WIN_SIZE_X,WIN_SIZE_Y);

    board = new Board();

    this->is_net_work = false;
}

GoHangWidget::~GoHangWidget()
{
    delete ui;

    delete board;
}

void GoHangWidget::paintEvent(QPaintEvent *event)
{
     QPainter painter(this);
     board->Draw(painter);

}

void GoHangWidget::mouseReleaseEvent(QMouseEvent *event)
{
    int x = (event->x() -OFFSET_X + cell_width/2)/cell_width;
    int y = (event->y() -OFFSET_Y + cell_height/2)/cell_height;


    if(x>=0 && x <= LINE_NUM_X && y >=0 && y<= LINE_NUM_Y)
    {
       if(this->is_can_move )
       {
           if(board->Click(x,y))
           {
                this->update();
               if(this->is_net_work)
               {
                   this->is_can_move = false;

                   //发送数据
                   char buf[128] = {0};
                   sprintf(buf,"%d,%d",x,y);
                   QTcpSocket *socket = TcpSocketHelper::getInstance()->getSocket();
                   TcpSocketHelper::getInstance()->sendMsg(PROTOCOL_DROPDOWM,this->other_user_id,strlen(buf));
                   socket->write(buf,strlen(buf));
               }
               if(board->is_end())
               {
                   this->is_can_move = false;
                   QMessageBox::information(NULL, "error", "游戏结束", QMessageBox::Yes, QMessageBox::No);
               }
           }
       }
    }
}

void GoHangWidget::init(bool is_net_work, QString black_name, QString white_name, char cur_type, uint32_t uid)
{
    this->board->init(is_net_work);
    this->is_net_work = is_net_work;
    if(cur_type == black)
        this->is_can_move = true;
    else
        this->is_can_move = false;
    ui->lbl_black->setText(black_name);
    ui->lbl_white->setText(white_name);
    this->other_user_id = uid;
}

void GoHangWidget::set_can_move(bool can_move)
{
    is_can_move = can_move;
}

void GoHangWidget::other_dropDown(int x, int y)
{
    if(board->Click(x,y))
    {
        this->update();
        this->is_can_move = true;

        if(board->is_end())
        {
            this->is_can_move = false;
            QMessageBox::information(NULL, "error", "游戏结束", QMessageBox::Yes, QMessageBox::No);
        }
    }
}
