#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMenu>
#include <QModelIndex>
#include "animationmodel.h"
#include "framedelegate.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->tableView->setModel(new SchMatrix::AnimationModel(this));
  ui->tableView->setItemDelegate(new SchMatrix::FrameDelegate(this));
  ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

  auto menu = new QMenu(this);
  menu->addAction("Test");

  connect(ui->tableView, &QTableView::customContextMenuRequested, this,
          [=](const QPoint& index) {
            qDebug() << ui->tableView->indexAt(index);
            if (ui->tableView->indexAt(index).isValid())
              menu->exec(QCursor::pos());
          });
}

MainWindow::~MainWindow() { delete ui; }
