#-------------------------------------------------
#
# Project created by QtCreator 2013-12-04T03:19:12
#
#-------------------------------------------------

QT       += network sql testlib core widgets

QT       -= gui

TARGET = servertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    servertestMain.cpp \
    ../userdb.cpp \
    ../session.cpp \
    ../server.cpp \
    dbtest.cpp \
    sessiontest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../userdb.h \
    ../session.h \
    ../server.h \
    dbtest.h \
    sessiontest.h
