#-------------------------------------------------
#
# Project created by QtCreator 2013-11-12T19:17:54
#
#-------------------------------------------------

QT       += core
QT       += widgets
QT       += sql widgets
QT       += network widgets
<<<<<<< HEAD
QT       += widgets

QT       -= gui
=======
QT       += gui
>>>>>>> 6bfebb45c594858ddfc199eda507235ec202efb9

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    session.cpp \
    userdb.cpp \
    server.cpp

HEADERS += \
    server.h \
    userdb.h \
    session.h

OTHER_FILES += \
    Doxyfile
