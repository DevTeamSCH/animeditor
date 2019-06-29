#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QModelIndex>
#include "animationmodel.h"
#include "framedelegate.h"
#include "layer.h"
#include "timelinemenu.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), animModel(this) {
  ui->setupUi(this);

  ui->tableView->setModel(&animModel);
  ui->tableView->setItemDelegate(new SchMatrix::FrameDelegate(this));
  ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

  auto menu = new SchMatrix::TimelineMenu(this);

  connect(ui->tableView, &QTableView::customContextMenuRequested, this,
          [=](const QPoint& idx) {
            if (ui->tableView->indexAt(idx).isValid())
              index = ui->tableView->indexAt(idx);
            animModel.setTime(33 * ui->tableView->indexAt(idx).column());
            qDebug() << ui->tableView->indexAt(idx);
            qDebug() << animModel.getTime() << '/' << animModel.getDuration();
            menu->exec(QCursor::pos());
          });

  connect(menu, &QMenu::triggered, this, &MainWindow::handleTimelineMenu);
}

MainWindow::~MainWindow() { delete ui; }

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
      break;
  }

  qDebug() << animModel.getLayer(index.row())->animations();
}
