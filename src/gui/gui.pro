#-------------------------------------------------
#
# Project created by QtCreator 2019-06-14T19:13:56
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

CONFIG += c++11

SOURCES += \
        colorpicker.cpp \
        framedelegate.cpp \
        graphicsscene.cpp \
        graphicsview.cpp \
        horizontalheader.cpp \
        horizontalheadercontrols.cpp \
        main.cpp \
        mainwindow.cpp \
        timelinemenu.cpp \
        timelineview.cpp

HEADERS += \
        colorpicker.h \
        framedelegate.h \
        graphicsscene.h \
        graphicsview.h \
        horizontalheader.h \
        horizontalheadercontrols.h \
        mainwindow.h \
        timelinemenu.h \
        timelineview.h

FORMS += \
        horizontalheadercontrols.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../core/release/ -llibanimeditor
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../core/debug/ -llibanimeditor
else:unix: LIBS += -L$$OUT_PWD/../core/ -llibanimeditor

INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core

# FFmpeg dlls
win32:LIBS += -L$$PWD/../../deps/win64/ffmpeg/bin

RESOURCES += \
    resources.qrc
