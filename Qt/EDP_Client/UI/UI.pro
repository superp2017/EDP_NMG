#-------------------------------------------------
#
# Project created by QtCreator 2018-08-04T15:42:25
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_FILE = app.rc




DESTDIR = ../../../bin
QMAKE_LIBDIR +=  ../../../bin
UI_DIR =../../../../temp/ui/EDP
OBJECTS_DIR = ../../../../temp/obj/EDP
MOC_DIR = ../../../../temp/moc/EDP

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    datacenter.cpp \
    sysconfig.cpp \
    form_home.cpp \
    form_datacollect.cpp \
    formmovecontrol.cpp \
    formcloudcontrol.cpp \
    formcommunicationsystem.cpp \
    formlogin.cpp \
    formcenter.cpp \
    formsystemsetting.cpp \
    dialognewcollectparam.cpp \
    dialognewcollectdata.cpp \
    plccontrol.cpp \
    testtcp.cpp

HEADERS += \
        mainwindow.h \
    datacenter.h \
    sysconfig.h \
    global.h \
    form_home.h \
    form_datacollect.h \
    formmovecontrol.h \
    formcloudcontrol.h \
    formcommunicationsystem.h \
    formlogin.h \
    formcenter.h \
    formsystemsetting.h \
    dialognewcollectparam.h \
    dialognewcollectdata.h \
    plccontrol.h \
    testtcp.h

FORMS += \
        mainwindow.ui \
    form_home.ui \
    form_datacollect.ui \
    formmovecontrol.ui \
    formcloudcontrol.ui \
    formcommunicationsystem.ui \
    formlogin.ui \
    formcenter.ui \
    formsystemsetting.ui \
    dialognewcollectparam.ui \
    dialognewcollectdata.ui \
    testtcp.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Data/release/ -lData
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Data/debug/ -lData
else:unix: LIBS += -L$$OUT_PWD/../Data/ -lData

INCLUDEPATH += $$PWD/../Data
DEPENDPATH += $$PWD/../Data

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../MySql/release/ -lMySql
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../MySql/debug/ -lMySql
else:unix: LIBS += -L$$OUT_PWD/../MySql/ -lMySql

INCLUDEPATH += $$PWD/../MySql
DEPENDPATH += $$PWD/../MySql

RESOURCES += \
    res.qrc
