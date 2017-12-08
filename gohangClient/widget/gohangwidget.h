#ifndef GOHANGWIDGET_H
#define GOHANGWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include "gohang/board.h"

namespace Ui {
class GoHangWidget;
}

class GoHangWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GoHangWidget(QWidget *parent = 0);
    ~GoHangWidget();

    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void init(bool is_net_work,
              QString black_name,
              QString white_name,
              char cur_type = black,
              uint32_t uid = 0);
    void set_can_move(bool can_move);

    void other_dropDown(int x,int y);
private:
    Ui::GoHangWidget *ui;
    Board *board;
    bool is_can_move;
    uint32_t other_user_id;
    bool is_net_work;
};

#endif // GOHANGWIDGET_H
