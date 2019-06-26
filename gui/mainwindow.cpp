#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "animationmodel.h"
#include "framedelegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->tableView->setModel(new SchMatrix::AnimationModel(this));
  ui->tableView->setItemDelegate(new SchMatrix::FrameDelegate(this));
}

MainWindow::~MainWindow() { delete ui; }
