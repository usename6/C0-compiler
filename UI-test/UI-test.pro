#-------------------------------------------------
#
# Project created by QtCreator 2019-05-25T09:49:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UI-test
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
INCLUDEPATH = ./include

SOURCES += \
        ./src/main.cpp \
        ./src/lexical.cpp\
        ./src/lookahead.cpp\
        ./src/midcode.cpp\
        ./src/parse.cpp\
        ./src/assemble.cpp\
        ./src/mainwindow.cpp \
        ./src/work.cpp

HEADERS += \
        ./include/assemble.h \
        ./include/lexical.h \
        ./include/lookahead.h \
        ./include/main.h \
        ./include/midcode.h \
        ./include/parse.h \
        ./include/mainwindow.h \
        ./include/work.h

FORMS += \
        ./form/mainwindow.ui \
        ./form/work.ui
