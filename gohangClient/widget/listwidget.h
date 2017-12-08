#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QListWidget>
#include <QContextMenuEvent>
#include <QMenu>
#include <QListWidgetItem>
#include <QAction>
#include <QCursor>
#include <Qvector>
#include "listitem.h"
#include "tcpsockethelper.h"
class ListWidget : public QListWidget
{
    Q_OBJECT
public:
    ListWidget(QWidget *parent = 0);

    void contextMenuEvent(QContextMenuEvent *event);

    ListItem *getItem();

    void clearAllItem();
private slots:
    void welcome();


private:
    QMenu* popMenu;

    QAction *action_welcome;

    ListItem *cur_item;

    QVector<ListItem *> item_pool;
};

#endif // LISTWIDGET_H
