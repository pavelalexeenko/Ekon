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
    login_window.cpp \
    main_window.cpp \
    database/db_service.cpp \
    database/user.cpp \
    tables/admin_widget.cpp \
    tables/worker_widget.cpp \
    tables_wigdet.cpp

HEADERS  += \
    login_window.h \
    main_window.h \
    database/db_service.h \
    database/user.h \
    tables/admin_widget.h \
    tables/worker_widget.h \
    tables_wigdet.h

CONFIG += c++11
