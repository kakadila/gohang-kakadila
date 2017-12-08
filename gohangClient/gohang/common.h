#ifndef CHESS_TYPE_H
#define CHESS_TYPE_H

#include <math.h>

#define max(a,b) (a>b?a:b)

typedef char chess_type;
const char no = 0;
const char white = 1;
const char black = 2;

struct Position
{
    Position(int x = 0,int y = 0)
    {
        this->x = x;
        this->y = y;
    }

    int x;
    int y;
    int score;

    int near(Position &pos)
    {
        int ax = abs(x-pos.x);
        int ay = abs(y-pos.y);
        return max(ax,ay);
    }

    void set(int x,int y)
    {
        this->x = x;
        this->y = y;
    }
};

#endif // CHESS_TYPE_H
