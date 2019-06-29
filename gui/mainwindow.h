#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <timelinemenu.h>
#include <QAction>
#include <QMainWindow>
#include <QModelIndex>
#include "animationmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void handleTimelineMenu(QAction *action);

 private:
  Ui::MainWindow *ui;
  QModelIndex index;
  SchMatrix::AnimationModel animModel;
};

#endif  // MAINWINDOW_H
