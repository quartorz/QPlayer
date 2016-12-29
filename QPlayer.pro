#-------------------------------------------------
#
# Project created by QtCreator 2016-09-10T19:01:31
#
#-------------------------------------------------

QT       += core gui multimediawidgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QPlayer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    customgraphicsview.cpp

HEADERS  += mainwindow.h \
    customgraphicsview.h

FORMS    += mainwindow.ui
