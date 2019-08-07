#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsWidget>
#include <QModelIndex>
#include "animationmodel.h"
#include "config.h"
#include "framedelegate.h"
#include "layer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_currentScene(
          new QGraphicsScene(0, 0, SchMatrix::width, SchMatrix::height, this)),
      m_animationModel(m_currentScene, this),
      m_actionGroup(this) {
  ui->setupUi(this);

  ui->tableView->setModel(&m_animationModel);
  ui->graphicsView->setScene(m_currentScene);
  ui->graphicsView->setModel(&m_animationModel);

  for (auto action : ui->mainToolBar->actions()) {
    m_actionGroup.addAction(action);
  }

  connect(&m_actionGroup, SIGNAL(triggered(QAction *)), ui->graphicsView,
          SLOT(updateCurrentTool(QAction *)));
}

MainWindow::~MainWindow() { delete ui; }
