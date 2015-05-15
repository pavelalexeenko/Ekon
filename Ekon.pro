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
    main_window.cpp \
    database/db_service.cpp \
    objects/user.cpp \
    tables/admin_widget.cpp \
    tables_wigdet.cpp \
    tables/secretary_widget.cpp \
    tables/worker_widget.cpp \
    implementations/control_widget.cpp \
    implementations/ekon_tables.cpp \
    dialogs/login_window.cpp \
    dialogs/add_user_dialog.cpp \
    dialogs/add_teacher_dialog.cpp \
    dialogs/add_discipline_dialog.cpp \
    tabs/load_calculation_widget.cpp \
    tabs/disciplines_widget.cpp \
    tabs/flows_widget.cpp \
    tabs/groups_widget.cpp \
    tabs/teachers_widget.cpp \
    tabs/users_widget.cpp \
    tabs/load_distribution_widget.cpp \
    objects/teacher.cpp \
    objects/discipline.cpp \
    objects/group.cpp \
    dialogs/add_group_dialog.cpp \
    objects/flow.cpp \
    dialogs/add_flow_dialog.cpp \
    dialogs/add_group_to_flow_dialog.cpp \
    dialogs/add_loadcalculation_dialog.cpp \
    implementations/check_box_delegate.cpp \
    implementations/read_only_delegate.cpp \
    implementations/checkable_sort_filter_proxy_model.cpp \
    dialogs/add_loaddistribution_dialog.cpp \
    objects/loadcalculation.cpp \
    implementations/hours_widget.cpp \
    objects/loaddistribution.cpp \
    objects/factors.cpp \
    dialogs/loaddistribution_dialog.cpp \
    dialogs/edit_loaddistribution_dialog.cpp \
    tabs/settings_widget.cpp

HEADERS  += \
    main_window.h \
    database/db_service.h \
    objects/user.h \
    tables/admin_widget.h \
    tables_wigdet.h \
    tables/secretary_widget.h \
    tables/worker_widget.h \
    implementations/control_widget.h \
    implementations/ekon_tables.h \
    dialogs/login_window.h \
    dialogs/add_user_dialog.h \
    dialogs/add_teacher_dialog.h \
    dialogs/add_discipline_dialog.h \
    tabs/load_calculation_widget.h \
    tabs/disciplines_widget.h \
    tabs/flows_widget.h \
    tabs/groups_widget.h \
    tabs/teachers_widget.h \
    tabs/users_widget.h \
    tabs/load_distribution_widget.h \
    objects/teacher.h \
    objects/discipline.h \
    objects/group.h \
    dialogs/add_group_dialog.h \
    objects/flow.h \
    dialogs/add_flow_dialog.h \
    dialogs/add_group_to_flow_dialog.h \
    dialogs/add_loadcalculation_dialog.h \
    implementations/check_box_delegate.h \
    implementations/read_only_delegate.h \
    implementations/checkable_sort_filter_proxy_model.h \
    dialogs/add_loaddistribution_dialog.h \
    objects/loadcalculation.h \
    implementations/hours_widget.h \
    objects/loaddistribution.h \
    objects/factors.h \
    dialogs/loaddistribution_dialog.h \
    dialogs/edit_loaddistribution_dialog.h \
    tabs/settings_widget.h

CONFIG += c++11

QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
QMAKE_LFLAGS += /SUBSYSTEM:CONSOLE,5.01
QMAKE_CXX += /D_USING_V110_SDK71_
LIBS *= -L"%ProgramFiles(x86)%/Microsoft SDKs/Windows/7.1A/Lib"
INCLUDEPATH += "%ProgramFiles(x86)%/Microsoft SDKs/Windows/7.1A/Include"


