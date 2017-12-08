#ifndef GAMEAI_H
#define GAMEAI_H

#include "common.h"
#include "config.h"
#include <QVector>

class GameAI
{
public:
   static Position move(chess_type chesses[][LINE_NUM_X], chess_type cur_drop_type);
   static bool is_end(chess_type chesses[][LINE_NUM_X]);
private:
   static void getPossibleMove(chess_type chesses[][LINE_NUM_X], QVector<Position> &all_pos, chess_type cur_drop_type, chess_type evaluate_type);
    static int evaluate_one_type(chess_type chesses[][LINE_NUM_X], chess_type cur_drop_type);
    static int evaluate(chess_type chesses[][LINE_NUM_X], chess_type cur_drop_type);

    static int getMax(chess_type chesses[][LINE_NUM_X], chess_type cur_drop_type, int step, int cur_min_score, int cur_score);
    static int getMin(chess_type chesses[][LINE_NUM_X],chess_type cur_drop_type,int step,int cur_max_score, int cur_score);

    static void printChess(chess_type chesses[][LINE_NUM_X]);

    static bool right(Position &pos,int del);
    static bool down(Position &pos,int del);
    static bool top_right(Position &pos,int del);
    static bool down_right(Position &pos,int del);
};


#endif // GAMEAI_H
