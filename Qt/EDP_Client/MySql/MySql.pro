#-------------------------------------------------
#
# Project created by QtCreator 2018-07-31T15:02:46
#
#-------------------------------------------------

QT       += sql

QT       -= gui

TARGET = MySql
TEMPLATE = lib

DEFINES += MYSQL_LIBRARY


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
        mysql.cpp

HEADERS += \
        mysql.h \
        mysql_global.h  

unix {
    target.path = /usr/lib
    INSTALLS += target
}



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Data/release/ -lData
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Data/debug/ -lData
else:unix: LIBS += -L$$OUT_PWD/../Data/ -lData

INCLUDEPATH += $$PWD/../Data
DEPENDPATH += $$PWD/../Data
