#-------------------------------------------------
#
# Project created by QtCreator 2018-03-02T14:45:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = animeditor
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


SOURCES += \
    main.cpp \
    ui/mainwindow.cpp \
    ui/frameelement.cpp \
    ui/pixelwidget.cpp \
    ui/pixelframe.cpp

HEADERS += \
    ui/mainwindow.h \
    ui/frameelement.h \
    ui/pixelwidget.h \
    ui/pixelframe.h

FORMS += \
    ui/mainwindow.ui \
    ui/frameelement.ui \
    ui/widget.ui \
    ui/pixelframe.ui
