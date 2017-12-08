#include "listwidget.h"

ListWidget::ListWidget(QWidget *parent)
    :QListWidget(parent)
{
    popMenu = new QMenu(this);
    action_welcome = new QAction("邀请", this);
    cur_item = NULL;

    connect(action_welcome, SIGNAL(triggered()), this, SLOT(welcome()));

    popMenu->addAction(action_welcome);
}

void ListWidget::contextMenuEvent(QContextMenuEvent *event)
{
       cur_item = (ListItem *)this->itemAt(mapFromGlobal(QCursor::pos()));
       if( cur_item!= NULL) //如果有item则添加"修改"菜单 [1]*
       {
             popMenu->exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置
       }
}

ListItem *ListWidget::getItem()
{
    ListItem *newitem = NULL;
    if(item_pool.size() >0)
    {
        newitem = item_pool.back();
        item_pool.pop_back();
        return newitem;
    }

    newitem = new ListItem(this);
    return newitem;
}

void ListWidget::clearAllItem()
{
    int item_num = this->count();
    for(int i = 0;i<item_num;++i)
    {
        ListItem *item = (ListItem*)this->takeItem(0);
        item_pool.push_back(item);
    }
}

void ListWidget::welcome()
{
    //发送挑战邀请
    char buf[] = "welcome";
    TcpSocketHelper::getInstance()->sendMsg(PROTOCOL_WELCOME,cur_item->user_id,strlen(buf));
    QTcpSocket *socket = TcpSocketHelper::getInstance()->getSocket();
    socket->write(buf,strlen(buf));
    cur_item = NULL;
}
