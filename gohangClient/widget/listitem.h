#ifndef LISTITEM_H
#define LISTITEM_H

#include <QListWidgetItem>

class ListItem : public QListWidgetItem
{
public:
    ListItem(QListWidget *parent);

    uint32_t user_id;
};

#endif // LISTITEM_H
