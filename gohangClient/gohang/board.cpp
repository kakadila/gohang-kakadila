#include "board.h"



Board::Board()
{
    init();
}

void Board::init(bool network)
{
    memset(m_chesses,0,sizeof(m_chesses));
    cur_drop_type = black;
    this->is_net_work = network;
}


bool Board::Click(int x, int y)
{
    if(m_chesses[y][x] != no)
        return false;

    //落子
    m_chesses[y][x] = cur_drop_type;
    change_cur_drop();

    if(!is_net_work)
    {
        //AI落子
        Position pos = GameAI::move(m_chesses,cur_drop_type);
        m_chesses[pos.y][pos.x] = cur_drop_type;
        change_cur_drop();
    }

    return true;

}

void Board::Draw(QPainter &painter)
{
    QBrush brush(QColor(200,200,125));
    painter.setBrush(brush);

    painter.drawRect(OFFSET_X,OFFSET_Y,BOARD_WIDTH,BOARD_HEIGHT);

    painter.setPen(Qt::black);
    int height = OFFSET_Y;
    int width = OFFSET_X;
    //先画竖线
    for(int i= 0;i<LINE_NUM_X;++i)
    {
        painter.drawLine(OFFSET_X,height,OFFSET_X+BOARD_WIDTH,height);
        height += cell_height;
    }
    //再画横线
    for(int i = 0;i<LINE_NUM_Y;++i)
    {
        painter.drawLine(width,OFFSET_Y,width,OFFSET_Y+BOARD_HEIGHT);
        width+= cell_width;
    }

    //绘制棋子
    height = OFFSET_Y;
    int half_cell_width = cell_width/2;
    int half_cell_height = cell_height/2;
    int factor = cell_width/10;
    for(int y = 0;y<LINE_NUM_Y;++y)
    {
        width = OFFSET_X;
        for(int x = 0;x<LINE_NUM_X;++x)
        {
            if(m_chesses[y][x] == white)
            {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(width-half_cell_width,height-half_cell_height,
                                    cell_width-factor,cell_height-factor);
            }else if(m_chesses[y][x] == black)
            {
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(width-half_cell_width,height-half_cell_height,
                                    cell_width-factor,cell_height-factor);
            }
            width+= cell_width;
        }
        height += cell_height;
    }
}

bool Board::is_end()
{
    return GameAI::is_end(m_chesses);
}

void Board::change_cur_drop()
{
    if(cur_drop_type == black)
        cur_drop_type = white;
    else
        cur_drop_type = black;
}


