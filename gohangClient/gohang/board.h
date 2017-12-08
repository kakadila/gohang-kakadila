#ifndef BOARD_H
#define BOARD_H

#include <QPainter>
#include <QPen>
#include <QBrush>
#include <string.h>
#include "config.h"
#include "common.h"
#include "gameai.h"

class Board
{
public:
    Board();

    void init(bool network = false);
    bool Click(int x,int y);
    void Draw(QPainter &painter);
    bool is_end();
private:
    //改变当前下棋的一方
    void change_cur_drop();
private:

    chess_type m_chesses[LINE_NUM_Y][LINE_NUM_X];

    chess_type cur_drop_type;  //当前下棋的一方

    bool is_net_work; //是否是网络
};

#endif // BOARD_H
