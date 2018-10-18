#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QGuiApplication>
#include <QScreen>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QPixmap pixmap(":/resources/img/splash1.jpg");
    QSplashScreen splash(pixmap.scaledToWidth(QGuiApplication::screens()[0]->size().width()/2));
    splash.show();
    MainWindow w;
    w.show();
    splash.finish(&w);
    return a.exec();
}
