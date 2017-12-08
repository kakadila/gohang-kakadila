#-------------------------------------------------
#
# Project created by QtCreator 2017-10-22T21:46:01
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = connectlinux
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    gohang/board.cpp \
    gohang/gameai.cpp \
    msg_handle/handle_list.cpp \
    msg_handle/handle_msg.cpp \
    widget/gohangwidget.cpp \
    widget/hallwidget.cpp \
    widget/listitem.cpp \
    widget/listwidget.cpp \
    widget/loginwidget.cpp \
    widget/registerwidget.cpp \
    widget/widget.cpp \
    main.cpp \
    tctsockethelper.cpp \
    uimanage.cpp \
    user_list.cpp



HEADERS += \
    gohang/board.h \
    gohang/common.h \
    gohang/config.h \
    gohang/gameai.h \
    msg_handle/msg_option/connect_handle.h \
    msg_handle/msg_option/login_handle.h \
    msg_handle/msg_option/register_user_handle.h \
    msg_handle/msg_option/update_userlist_handle.h \
    msg_handle/msg_option/user_info_handle.h \
    msg_handle/msg_option/welcome_handle.h \
    msg_handle/handle_base.h \
    msg_handle/handle_list.h \
    msg_handle/handle_msg.h \
    widget/gohangwidget.h \
    widget/hallwidget.h \
    widget/listitem.h \
    widget/listwidget.h \
    widget/loginwidget.h \
    widget/registerwidget.h \
    widget/widget.h \
    msg.h \
    protocol.h \
    tcpsockethelper.h \
    uimanage.h \
    user_list.h \
    msg_handle/msg_option/dropdown_handle.h



FORMS += \
    widget/gohangwidget.ui \
    widget/hallwidget.ui \
    widget/loginwidget.ui \
    widget/registerwidget.ui \
    widget/widget.ui

