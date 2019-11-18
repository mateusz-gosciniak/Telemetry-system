#-------------------------------------------------
#
# Project created by QtCreator 2016-07-11T10:28:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = System_telemetrii
TEMPLATE = app


SOURCES += main.cpp\
        klasaglowna.cpp \
    okno3d.cpp \
    sztuczny_horyzont.cpp

HEADERS  += klasaglowna.h \
    obj_load.hpp \
    okno3d.h \
    sztuczny_horyzont.h

FORMS    += klasaglowna.ui

RESOURCES += \
    zasoby.qrc
