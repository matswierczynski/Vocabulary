#-------------------------------------------------
#
# Project created by QtCreator 2015-05-23T15:04:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Program
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Scheduler.cpp \
    Slowko.cpp \
    Slownik.cpp

HEADERS  += mainwindow.h \
    Scheduler.h \
    Slowko.h \
    Slownik.h

FORMS    += mainwindow.ui
