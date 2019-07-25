#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QGraphicsScene>
#include <QMainWindow>
#include "animationmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  QGraphicsScene *currentScene;
  SchMatrix::AnimationModel animModel;
};

#endif  // MAINWINDOW_H
