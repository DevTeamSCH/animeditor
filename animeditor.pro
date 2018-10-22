#-------------------------------------------------
#
# Project created by QtCreator 2018-10-18T15:20:44
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = animeditor
TEMPLATE = app
INCLUDEPATH += lib/libanimeditor/include
INCLUDEPATH += lib/Qt-Color-Widgets/include/QtColorWidgets
include(lib/Qt-Color-Widgets/color_widgets.pri)

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QTCOLORWIDGETS_STATICALLY_LINKED

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

HEADERS += \
    src/aboutdialog.h \
    src/mainwindow.h \
    src/matrixview.h \
    src/matrixscene.h \
    src/pixelquartetwidget.h \
    src/pixelwidget.h

SOURCES += \
    src/aboutdialog.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/matrixview.cpp \
    src/matrixscene.cpp \
    src/pixelquartetwidget.cpp \
    src/pixelwidget.cpp

FORMS += \
    src/aboutdialog.ui \
    src/mainwindow.ui

RESOURCES += \
    resource.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
