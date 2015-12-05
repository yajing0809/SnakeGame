#-------------------------------------------------
#
# Project created by QtCreator 2014-11-14T14:03:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SnakeGame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    quitwidget.cpp \
    gameboard.cpp

HEADERS  += mainwindow.h \
    quitwidget.h \
    gameboard.h

FORMS    += mainwindow.ui \
    quitwidget.ui \
    gameboard.ui
