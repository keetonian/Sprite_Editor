#-------------------------------------------------
#
# Project created by QtCreator 2016-04-13T09:21:51
#
#-------------------------------------------------

QT       += core gui

#QMAKE_CXXFLAGS += -std=c++0x
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = A7-Parachutes
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    Trie/Node.cpp \
    Trie/Trie.cpp \
    echoclient.cpp \
    leveldialog.cpp \
    registrationDialog.cpp \
    gamewindow.cpp \
    game.cpp

HEADERS  += mainwindow.h \
    Trie/Node.h \
    Trie/Trie.h \
    echoclient.h \
    leveldialog.h \
    registrationDialog.h \
    gamewindow.h \
    game.h

FORMS    += mainwindow.ui \
    leveldialog.ui \
    registrationDialog.ui \
    gamewindow.ui

RESOURCES += \
    images.qrc

include(Box2D/Box2D.pro)

win32|macx {
    QT += websockets
}
unix:!macx {
    include(QtWebSockets/websockets.pro)
}
