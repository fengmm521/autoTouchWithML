#-------------------------------------------------
#
# Project created by QtCreator 2014-10-21T10:20:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CH9326DEG
TEMPLATE = app

SOURCES += main.cpp\
        ch9326debug.cpp

HEADERS  += ch9326debug.h

FORMS    += ch9326dlg.ui

QT += qt3support

LIBS += -lusb\
    -lch9326

# No need to add
#INCLUDEPATH += /usr/local/include/libusb-1.0
#DEPENDPATH += /usr/local/include/libusb-1.0




