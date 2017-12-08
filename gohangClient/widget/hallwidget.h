#ifndef HALLWIDGET_H
#define HALLWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QTableWidgetItem>
#include "listwidget.h"

namespace Ui {
class HallWidget;
}

class HallWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HallWidget(QWidget *parent = 0);
    ~HallWidget();

    void showUpdate();

private slots:
    void on_btn_update_clicked();

    void on_pushButton_clicked();

private:
    Ui::HallWidget *ui;
};

#endif // HALLWIDGET_H
