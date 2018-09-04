#-------------------------------------------------
#
# Project created by QtCreator 2018-07-31T16:49:32
#
#-------------------------------------------------

QT       -= gui

TARGET = Data
TEMPLATE = lib

DEFINES += DATA_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DESTDIR = ../../../bin
QMAKE_LIBDIR +=  ../../../bin
UI_DIR =../../../../temp/ui/EDP
OBJECTS_DIR = ../../../../temp/obj/EDP
MOC_DIR = ../../../../temp/moc/EDP

SOURCES += \
        data.cpp

HEADERS += \
        data.h \
        data_global.h 

unix {
    target.path = /usr/lib
    INSTALLS += target
}
