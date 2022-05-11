#-------------------------------------------------
#
# Project created by QtCreator 2013-08-22T22:46:33
#
#-------------------------------------------------

QT       += core gui multimedia

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TowerDefense
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    towerposition.cpp \
    tower.cpp \
    waypoint.cpp \
    enemy.cpp \
    bullet.cpp \
    audioplayer.cpp \
    plistreader.cpp \
    tighttowerposi.cpp \
    arrowtower.cpp \
    barbette.cpp \
    singlecado.cpp \
    startwindow.cpp \
    winwindow.cpp \
    lostwindow.cpp \
    middlewindow.cpp

HEADERS  += mainwindow.h \
    towerposition.h \
    tower.h \
    waypoint.h \
    utility.h \
    enemy.h \
    bullet.h \
    audioplayer.h \
    plistreader.h \
    tighttowerposi.h \
    arrowtower.h \
    barbette.h \
    singlecado.h \
    startwindow.h \
    winwindow.h \
    lostwindow.h \
    middlewindow.h

FORMS    += mainwindow.ui \
    startwindow.ui \
    winwindow.ui \
    lostwindow.ui \
    middlewindow.ui

RESOURCES += \
    resource.qrc
