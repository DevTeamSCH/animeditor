#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QModelIndex>
#include "animationmodel.h"
#include "config.h"
#include "framedelegate.h"
#include "layer.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      animModel(this),
      timelineMenu(this) {
  ui->setupUi(this);

  ui->tableView->setModel(&animModel);
  ui->tableView->setItemDelegate(new SchMatrix::FrameDelegate(this));
  ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

  connect(ui->tableView, &QWidget::customContextMenuRequested, this,
          &MainWindow::handleTimelineMenuRequest);
  connect(&timelineMenu, &QMenu::triggered, this,
          &MainWindow::handleTimelineMenu);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::handleTimelineMenuRequest(const QPoint& idx) {
  if (!ui->tableView->indexAt(idx).isValid()) return;

  index = ui->tableView->indexAt(idx);

  animModel.setTime(SchMatrix::frameLength *
                    ui->tableView->indexAt(idx).column());

  timelineMenu.exec(QCursor::pos());
}

void MainWindow::handleTimelineMenu(QAction* action) {
  switch (action->data().toInt()) {
    case SchMatrix::MenuEntry::CreateClassicTween:
      break;
    case SchMatrix::MenuEntry::InsertFrame:
      animModel.setData(index, SchMatrix::FrameTypes::Frame);
      break;
    case SchMatrix::MenuEntry::RemoveFrame:
      animModel.removeData(index);
      break;
    case SchMatrix::MenuEntry::InsertKeyframe: {
      auto layer = animModel.getLayer(index.row());

      // check if previous Keyframe is empty
      animModel.setData(index, (layer->currentKeyframe()->animationCount())
                                   ? SchMatrix::FrameTypes::BlankKey
                                   : SchMatrix::FrameTypes::BlankKey);
      break;
    }
    case SchMatrix::MenuEntry::InsertBlankKeyframe:
      animModel.setData(index, SchMatrix::FrameTypes::BlankKey);
      break;
    case SchMatrix::MenuEntry::ClearFrames:
      break;
    case SchMatrix::MenuEntry::SelectAllFrames:
      int row = index.row();

      QModelIndex left = animModel.index(row, 0);
      QModelIndex right = animModel.index(row, animModel.elementCount(row) - 1);

      QItemSelection selection(left, right);
      ui->tableView->selectionModel()->clear();
      ui->tableView->selectionModel()->select(selection,
                                              QItemSelectionModel::Select);
      break;
  }

  auto layer = animModel.getLayer(index.row());

  qDebug() << layer->animations();
  for (auto l : layer->pauses()) {
    qDebug() << l << l->duration();
  }
}
