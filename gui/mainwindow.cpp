#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsWidget>
#include <QModelIndex>
#include "animationmodel.h"
#include "config.h"
#include "framedelegate.h"
#include "graphicswidget.h"
#include "layer.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      currentScene(
          new QGraphicsScene(0, 0, SchMatrix::width, SchMatrix::height, this)),
      animModel(currentScene, this),
      actionGroup(this) {
  ui->setupUi(this);

  ui->tableView->setModel(&animModel);
  ui->graphicsView->setScene(currentScene);

  for (auto action : ui->mainToolBar->actions()) {
    actionGroup.addAction(action);
  }
}

MainWindow::~MainWindow() { delete ui; }
