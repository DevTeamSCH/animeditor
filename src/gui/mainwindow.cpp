#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsWidget>
#include <QModelIndex>
#include <QSettings>
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
      m_actionGroup(this),
      m_penColorPicker(Qt::black),
      m_brushColorPicker(Qt::white) {
  ui->setupUi(this);

  ui->tableView->setModel(&m_animationModel);
  ui->graphicsView->setScene(m_currentScene);
  ui->graphicsView->setModel(&m_animationModel);

  // Zoom graphicsView to make the scene not too small
  ui->graphicsView->fitInView(0, 0, 3, 3, Qt::KeepAspectRatio);

  for (auto action : ui->mainToolBar->actions()) {
    m_actionGroup.addAction(action);
  }

  // Add color pickers for pen and brush color
  m_penColorPicker.setToolTip(tr("Stroke Color"));
  m_brushColorPicker.setToolTip(tr("Fill Color"));
  ui->mainToolBar->addWidget(&m_penColorPicker);
  ui->mainToolBar->addWidget(&m_brushColorPicker);

  // Settings creation
  QSettings settings;

  settings.beginGroup("MainWindow");
  settings.setValue("penColor", m_penColorPicker.currentColor());
  settings.setValue("brushColor", m_brushColorPicker.currentColor());
  settings.endGroup();

  connect(&m_actionGroup, SIGNAL(triggered(QAction *)), ui->graphicsView,
          SLOT(updateCurrentTool(QAction *)));
  connect(&m_penColorPicker, SIGNAL(currentColorChanged(QColor)), this,
          SLOT(updatePenColor(QColor)));
  connect(&m_brushColorPicker, SIGNAL(currentColorChanged(QColor)), this,
          SLOT(updateBrushColor(QColor)));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::updatePenColor(const QColor &color) {
  QSettings settings;
  settings.setValue("MainWindow/penColor", m_penColorPicker.currentColor());
}

void MainWindow::updateBrushColor(const QColor &color) {
  QSettings settings;
  settings.setValue("MainWindow/brushColor", m_brushColorPicker.currentColor());
}
