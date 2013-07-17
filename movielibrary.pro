#-------------------------------------------------
#
# Project created by QtCreator 2013-07-09T07:45:55
#
#-------------------------------------------------

QT       += core gui network xml sql phonon

INCLUDEPATH += C:/Data/Projects/Qt_Projects/qjson-build/lib

LIBS += -LC:/Data/Projects/Qt_Projects/qjson-build/lib -lqjson

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = movielibrary
TEMPLATE = app

SOURCES += main.cpp\
        movielibrary.cpp \
    rottentomatoes.cpp \
    twitter.cpp \
    moviedb.cpp \
    piratebay.cpp

HEADERS  += movielibrary.h \
    rottentomatoes.h \
    twitter.h \
    moviedb.h \
    piratebay.h

FORMS    += movielibrary.ui

RESOURCES += \
    resources.qrc
