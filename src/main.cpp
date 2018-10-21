#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QGuiApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    #ifndef QT_DEBUG
    QPixmap pixmap(":/resources/img/splash1.jpg");
    QSplashScreen splash(pixmap.scaledToWidth(QGuiApplication::screens()[0]->size().width()/2));
    splash.show();
    #endif
    MainWindow w;
    w.show();
    #ifndef QT_DEBUG
    splash.finish(&w);
    #endif
    return a.exec();
}
