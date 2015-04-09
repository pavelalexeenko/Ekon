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
    database/user.cpp

HEADERS  += \
    login_window.h \
    main_window.h \
    database/db_service.h \
    database/user.h

CONFIG += c++11
