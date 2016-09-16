#-------------------------------------------------
#
# Project created by QtCreator 2016-08-25T16:32:57
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 6dof
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    basic6dof.cpp \
    servo6dof.cpp

HEADERS  += mainwindow.h \
    basic6dof.h \
    servo6dof.h

FORMS    += mainwindow.ui
