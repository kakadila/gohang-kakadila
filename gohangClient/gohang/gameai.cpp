#include "gameai.h"
#include <QDebug>
#include <QtAlgorithms>
#include <iostream>

//各类棋型分数
static int SCORE[6] =
{
    10,  //第敌方棋子时候的减去分数
    12, //1个连着
    50, //2个连着
    200, //3个连着
    1500, //4个连着
    100000//5个连着
};

static int cut = 0;

static bool less(Position &a,Position &b)
{
    return a.score<b.score;
}

static bool greater(Position &a,Position &b)
{
    return a.score>b.score;
}

Position GameAI::move(chess_type chesses[][LINE_NUM_X], chess_type cur_drop_type)
{
    cut = 0;
    Position pos;
    QVector<Position> all_pos;
    getPossibleMove(chesses,all_pos,cur_drop_type,cur_drop_type);
    qSort(all_pos.begin(),all_pos.end(),greater);

    int branch = all_pos.length() < MAX_BRANCH?all_pos.length():MAX_BRANCH;

    int max_score = -999999;
    int cur_score;
    pos = all_pos[0];
    for(int i = 0;i<branch;++i)
    {
        chesses[all_pos[i].y][all_pos[i].x] = cur_drop_type;
        cur_score = getMin(chesses,cur_drop_type,2,max_score,all_pos[i].score);
        chesses[all_pos[i].y][all_pos[i].x] = no;

        if(cur_score > max_score)
        {
            max_score = cur_score;
            pos = all_pos[i];
        }
    }


   // qDebug()<<cut;
    return pos;
}

bool GameAI::is_end(chess_type chesses[][LINE_NUM_X])
{
    int score = evaluate(chesses,black);
    if(abs(score) >= SCORE[5])
    {
        return true;
    }

    return false;
}

void GameAI::getPossibleMove(chess_type chesses[][LINE_NUM_X], QVector<Position> &all_pos,
                             chess_type cur_drop_type,chess_type evaluate_type)
{
    Position tmp_pos;
    for(int y=0;y<LINE_NUM_Y;++y)
    {
        for(int x = 0;x<LINE_NUM_X;++x)
        {
            if(chesses[y][x] == no)
            {
                tmp_pos.x = x;
                tmp_pos.y = y;
                chesses[y][x] = evaluate_type;
                tmp_pos.score = evaluate(chesses,cur_drop_type);
                chesses[y][x] = no;
                all_pos.push_back(tmp_pos);
                if(abs(tmp_pos.score) >= SCORE[5])
                {
                    return;
                }
            }
        }
    }
}



int GameAI::evaluate_one_type(chess_type chesses[][LINE_NUM_X], chess_type cur_drop_type)
{
    chess_type hostile; //敌方
    if(cur_drop_type == black)
        hostile = white;
    else
        hostile = black;

    //开始计分
    int all_score = 0;
    Position cur_pos,next_pos;
    int count;
    int i;

    //横向
    for(int y = 0;y < LINE_NUM_Y;++y)
    {
        for(int x = 0;x < LINE_NUM_X-4;++x)
        {
            cur_pos.set(x,y);
            next_pos = cur_pos;
            if(right(next_pos,4)){
                count = 0;
                for(i = 0;i<5;++i)
                {
                    if(chesses[cur_pos.y][cur_pos.x] == cur_drop_type)
                        ++count;
                    else if(chesses[cur_pos.y][cur_pos.x] == hostile)
                    {
                        all_score -= SCORE[0];
                        break;
                    }

                    if(!right(cur_pos,1))
                    {
                        break;
                    }
                }
                if(count == 5) return SCORE[count];
                all_score += SCORE[count];
            }
        }
    }

    //纵向
    for(int y = 0;y < LINE_NUM_Y-4;++y)
    {
        for(int x = 0;x < LINE_NUM_X;++x)
        {
            cur_pos.set(x,y);
            next_pos = cur_pos;
            if(down(next_pos,4)){
                count = 0;
                for(i = 0;i<5;++i)
                {
                    if(chesses[cur_pos.y][cur_pos.x] == cur_drop_type)
                        ++count;
                    else if(chesses[cur_pos.y][cur_pos.x] == hostile)
                    {
                        all_score -= SCORE[0];
                        break;
                    }

                    if(!down(cur_pos,1))
                    {
                        break;
                    }
                }
                if(count == 5 ) return SCORE[count];
                all_score += SCORE[count];
            }
        }
    }

    //斜下
    for(int y = 0;y < LINE_NUM_Y-4;++y)
    {
        for(int x = 0;x<LINE_NUM_X;++x)
        {
            cur_pos.set(x,y);
            next_pos = cur_pos;
            if(down_right(next_pos,4)){
                count = 0;
                for(i = 0;i<5;++i)
                {
                    if(chesses[cur_pos.y][cur_pos.x] == cur_drop_type)
                        ++count;
                    else if(chesses[cur_pos.y][cur_pos.x] == hostile)
                    {
                       all_score -= SCORE[0];
                        break;
                    }

                    if(!down_right(cur_pos,1))
                    {
                        break;
                    }
                }
                if(count == 5 ) return SCORE[count];
                all_score += SCORE[count];
            }else
                break;
        }
    }
    for(int x = 0;x < LINE_NUM_X-4;++x)
    {
        for(int y = 0;y<LINE_NUM_Y;++y)
        {
            cur_pos.set(x,y);
            next_pos = cur_pos;
            if(down_right(next_pos,4)){
                count = 0;
                for(i = 0;i<5;++i)
                {
                    if(chesses[cur_pos.y][cur_pos.x] == cur_drop_type)
                        ++count;
                    else if(chesses[cur_pos.y][cur_pos.x] == hostile)
                    {
                        all_score -= SCORE[0];
                        break;
                    }

                    if(!down_right(cur_pos,1))
                    {
                        break;
                    }
                }
                if(count == 5) return SCORE[count];
                all_score += SCORE[count];
            }else
                break;
        }
    }

    //斜上
    for(int x = 0;x < LINE_NUM_X-4;++x)
    {
        for(int y = LINE_NUM_Y-1;y>=0;--y)
        {
            cur_pos.set(x,y);
            next_pos = cur_pos;
            if(top_right(next_pos,4)){
                count = 0;
                for(i = 0;i<5;++i)
                {
                    if(chesses[cur_pos.y][cur_pos.x] == cur_drop_type)
                        ++count;
                    else if(chesses[cur_pos.y][cur_pos.x] == hostile)
                    {
                        all_score -= SCORE[0];
                        break;
                    }

                    if(!top_right(cur_pos,1))
                    {
                        break;
                    }
                }
                if(count == 5 ) return SCORE[count];
                all_score += SCORE[count];
            }else
                break;
        }
    }
    for(int y = 4;y < LINE_NUM_Y;++y)
    {
        for(int x = 0;x<LINE_NUM_X;++x)
        {
            cur_pos.set(x,y);
            next_pos = cur_pos;
            if(top_right(next_pos,4)){
                count = 0;
                for(i = 0;i<5;++i)
                {
                    if(chesses[cur_pos.y][cur_pos.x] == cur_drop_type)
                        ++count;
                    else if(chesses[cur_pos.y][cur_pos.x] == hostile)
                    {
                        all_score -= SCORE[0];
                        break;
                    }

                    if(!top_right(cur_pos,1))
                    {
                        break;
                    }
                }
                if(count == 5 ) return SCORE[count];
                all_score += SCORE[count];
            }else
                break;
        }
    }


    return all_score;
}

int GameAI::evaluate(chess_type chesses[][LINE_NUM_X], chess_type cur_drop_type)
{
    chess_type hostile; //敌方
    if(cur_drop_type == black)
        hostile = white;
    else
        hostile = black;

    int cur_drop_score = evaluate_one_type(chesses,cur_drop_type);
    if(cur_drop_score >= SCORE[5])
    {
      //  printChess(chesses);
        return cur_drop_score;
    }

    int hostile_score = evaluate_one_type(chesses,hostile);
    if(hostile_score >= SCORE[5])
    {
       // printChess(chesses);
        return -hostile_score;
    }

    return cur_drop_score - hostile_score;
}


int GameAI::getMax(chess_type chesses[][LINE_NUM_X], chess_type cur_drop_type,
                   int step,int cur_min_score,int cur_score)
{
    if(step > AI_THINK_STEP || abs(cur_score) == SCORE[5])
    {
        return cur_score;
    }

    QVector<Position> all_pos;
    getPossibleMove(chesses,all_pos,cur_drop_type,cur_drop_type);
    qSort(all_pos.begin(),all_pos.end(),greater);

    int max_score = -999999;
    int branch = all_pos.length() < MAX_BRANCH?all_pos.length():MAX_BRANCH;

    for(int i = 0;i<branch;++i)
    {
        chesses[all_pos[i].y][all_pos[i].x] = cur_drop_type;
        cur_score = getMin(chesses,cur_drop_type,step+1,max_score,all_pos[i].score);
        chesses[all_pos[i].y][all_pos[i].x] = no;
        if(cur_score >= cur_min_score)
        {
            ++cut;
            return cur_score;
        }
        if(cur_score > max_score)
        {
            max_score = cur_score;
        }
    }
    return max_score;
}

int GameAI::getMin(chess_type chesses[][LINE_NUM_X], chess_type cur_drop_type,
                   int step,int cur_max_score,int cur_score)
{
    if(step > AI_THINK_STEP || abs(cur_score) == SCORE[5])
    {
        return cur_score;
    }

    QVector<Position> all_pos;
    chess_type hostile = cur_drop_type==black?white:black;
    getPossibleMove(chesses,all_pos,cur_drop_type,hostile);
    qSort(all_pos.begin(),all_pos.end(),less);
    if(all_pos[0].score == -SCORE[5])
    {
        std::cout<<step<<std::endl;
    }
    int min_score = 999999;
    int branch = all_pos.length() < MAX_BRANCH?all_pos.length():MAX_BRANCH;

    for(int i = 0;i<branch;++i)
    {
        chesses[all_pos[i].y][all_pos[i].x] = hostile;
        cur_score = getMax(chesses,cur_drop_type,step+1,min_score,all_pos[i].score);
        chesses[all_pos[i].y][all_pos[i].x] = no;
        if(cur_score <= cur_max_score)
        {
            ++cut;
            return cur_score;
        }
        if(cur_score < min_score)
        {
            min_score = cur_score;
        }
    }
    return min_score;
}

void GameAI::printChess(chess_type chesses[][LINE_NUM_X])
{
    std::cout<<"==================="<<std::endl;
    for(int y =0;y<LINE_NUM_Y;++y)
    {
        for(int x = 0;x<LINE_NUM_X;++x)
        {
            switch(chesses[y][x])
            {
            case black:
                std::cout<<"*";
                break;
            case white:
                std::cout<<"0";
                break;
             default:
                std::cout<<"-";
                break;
            }
        }
        std::cout<<std::endl;
    }
   std::cout<<"==================="<<std::endl;
}

bool GameAI::right(Position &pos, int del)
{
    pos.x += del;
    if(pos.x >= LINE_NUM_X)
    {
        return false;
    }
    return true;
}

bool GameAI::down(Position &pos, int del)
{
    pos.y += del;
    if(pos.y>= LINE_NUM_Y)
        return false;
    return true;
}

bool GameAI::top_right(Position &pos, int del)
{
    pos.x += del;
    pos.y -= del;
    if(pos.x >= LINE_NUM_X || pos.y <0)
    {
        return false;
    }
    return true;
}

bool GameAI::down_right(Position &pos, int del)
{
    pos.x += del;
    pos.y += del;
    if(pos.x >= LINE_NUM_X || pos.y>= LINE_NUM_Y)
    {
        return false;
    }
    return true;
}
