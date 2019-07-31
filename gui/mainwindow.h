#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QActionGroup>
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
  QActionGroup actionGroup;
};

#endif  // MAINWINDOW_H
