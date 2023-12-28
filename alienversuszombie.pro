#-------------------------------------------------
#
# Project created by QtCreator 2020-07-13T11:03:49
#
#-------------------------------------------------

QT       += core gui


CONFIG+=static
QMAKE_LFLAGS+=-static -static-libgcc -static-libstdc++ -lstdc++
DEFINES+=STATIC
VERSION = 1.0.0

DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AlienVersusZombie
TEMPLATE = app
RC_ICONS = pic/alienversuszombie.ico

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    gamescene.cpp \
    soundplayer.cpp \
    zombie.cpp \
    pacemaker.cpp \
    alien.cpp

HEADERS += \
        mainwindow.h \
    gamescene.h \
    soundplayer.h \
    gameproperties.h \
    zombie.h \
    pacemaker.h \
    alien.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    pic.qrc


INCLUDEPATH +=$$(PORT_AUDIO_ROOT)/include
LIBS += $$PWD/audio/music.raw.o
LIBS += $$PWD/audio/fail.raw.o
LIBS += $$PWD/audio/win.raw.o
LIBS += $$PWD/audio/event.raw.o

LIBS += -L$$(PORT_AUDIO_ROOT)/lib/ -lportaudio


INCLUDEPATH +=$$(SHOWLICENSE_ROOT)
LIBS += -L$$(SHOWLICENSE_ROOT) -lshowlicense
