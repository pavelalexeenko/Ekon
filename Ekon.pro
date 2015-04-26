#-------------------------------------------------
#
# Project created by QtCreator 2015-03-08T16:32:17
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ekon
TEMPLATE = app


SOURCES += main.cpp\
    dialogs/login_window.cpp \
    main_window.cpp \
    database/db_service.cpp \
    database/user.cpp \
    tables/admin_widget.cpp \
    tables_wigdet.cpp \
    tables/secretary_widget.cpp \
    tables/worker_widget.cpp \
    implementations/checkbox_item_delegate.cpp \
    implementations/centered_checkbox.cpp \
    dialogs/add_user_dialog.cpp \
    dialogs/add_teacher_dialog.cpp \
    dialogs/add_discipline_dialog.cpp \
    implementations/control_widget.cpp \
    tabs/users_tab_widget.cpp \
    implementations/ekon_tables.cpp

HEADERS  += \
    dialogs/login_window.h \
    main_window.h \
    database/db_service.h \
    database/user.h \
    tables/admin_widget.h \
    tables_wigdet.h \
    tables/secretary_widget.h \
    tables/worker_widget.h \
    implementations/checkbox_item_delegate.h \
    implementations/centered_checkbox.h \
    dialogs/add_user_dialog.h \
    dialogs/add_teacher_dialog.h \
    dialogs/add_discipline_dialog.h \
    implementations/control_widget.h \
    tabs/users_tab_widget.h \
    implementations/ekon_tables.h

CONFIG += c++11
