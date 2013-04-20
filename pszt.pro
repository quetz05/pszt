#-------------------------------------------------
#
# Project created by QtCreator 2013-04-20T12:52:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pszt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    symulation.cpp \
    planeta.cpp \
    kometa.cpp \
    vector.cpp \
    algorytm.cpp

HEADERS  += mainwindow.h \
    planeta.h \
    vector.h \
    symulation.h \
    kometa.h \
    algorytm.h

FORMS += \
    mainwindow.ui
