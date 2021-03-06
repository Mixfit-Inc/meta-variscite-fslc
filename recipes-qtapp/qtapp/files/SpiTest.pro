#-------------------------------------------------
#
# Project created by QtCreator 2018-02-08T12:09:17
#
#-------------------------------------------------

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtapp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    spirpi.cpp \
    bytedatarappresentation.cpp \
    targetUiElement.cpp \
    intelhex.cpp \
    server.cpp

HEADERS  += mainwindow.h \
    spirpi.h \
    bytedatarappresentation.h \
    targetUiElement.h \
    intelhex.h \
    server.h

FORMS    += mainwindow.ui \
    bytedatarappresentation.ui \
    targetUiElement.ui

RESOURCES += \
    resources.qrc

target.path = /usr/bin
INSTALLS += target
