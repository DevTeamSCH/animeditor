#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QActionGroup>
#include <QGraphicsScene>
#include <QMainWindow>
#include "animationmodel.h"
#include "colorpicker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void updatePenColor(const QColor &color);
  void updateBrushColor(const QColor &color);

 private:
  Ui::MainWindow *ui;
  QGraphicsScene *m_currentScene;
  SchMatrix::AnimationModel m_animationModel;
  QActionGroup m_actionGroup;
  SchMatrix::ColorPicker m_penColorPicker;
  SchMatrix::ColorPicker m_brushColorPicker;
};

#endif  // MAINWINDOW_H
