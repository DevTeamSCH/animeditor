#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  // Set data for QSettings
  a.setOrganizationName("KSZK");
  a.setOrganizationDomain("kszk.bme.hu");
  a.setApplicationName("AnimEditor");

  MainWindow w;
  w.show();

  return a.exec();
}
