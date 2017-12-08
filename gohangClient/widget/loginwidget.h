#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "tcpsockethelper.h"

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();

private slots:

    void on_btn_login_clicked();

    void on_btn_register_clicked();

private:
    Ui::LoginWidget *ui;
    QTcpSocket *socket;

};

#endif // LOGINWIDGET_H
