#include "timelineview.h"

#include <QDebug>
#include <QHeaderView>
#include <QModelIndex>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QScrollBar>
#include "animationmodel.h"
#include "config.h"
#include "framedelegate.h"
#include "keyframe.h"
#include "layer.h"

namespace SchMatrix {

TimelineView::TimelineView(QWidget *parent)
    : QTableView(parent), animModel(nullptr), header(this), timelineMenu(this) {
  setHorizontalHeader(&header);
  setItemDelegate(new SchMatrix::FrameDelegate(this));

  connect(&timelineMenu, &QMenu::triggered, this, &TimelineView::handleMenu);
}

void TimelineView::paintEvent(QPaintEvent *event) {
  // use default render
  QTableView::paintEvent(event);

  // use custom render
  auto firstVisualColumn = horizontalHeader()->visualIndexAt(0);
  auto lastVisualColumn = horizontalHeader()->visualIndexAt(
      horizontalHeader()->viewport()->width());

  if (firstVisualColumn == -1) firstVisualColumn = 0;
  if (lastVisualColumn == -1)
    lastVisualColumn = horizontalHeader()->count() - 1;

  auto currentColumn = animModel->getCurrentFrame();

  // outside of visual range
  if (currentColumn < firstVisualColumn || currentColumn > lastVisualColumn)
    return;

  auto colWidth = columnWidth(0);
  auto posX = columnViewportPosition(currentColumn);

  posX += colWidth / 2;

  QPainter painter(viewport());

  painter.setPen(Qt::red);
  painter.drawLine(posX, 0, posX, viewport()->height());
}

void TimelineView::mousePressEvent(QMouseEvent *event) {
  QTableView::mousePressEvent(event);

  if (!(event->buttons() & Qt::LeftButton) &&
      !(event->buttons() & Qt::RightButton))
    return;

  auto index = indexAt(event->pos());

  if (!index.isValid()) return;

  // Set current layer by index
  animModel->setCurrentLayer(index.row());

  animModel->setFrame(index.column());
}

void TimelineView::handleMenu(QAction *action) {
  switch (action->data().toInt()) {
    case SchMatrix::MenuEntry::CreateClassicTween:
      break;
    case SchMatrix::MenuEntry::InsertFrame:
      animModel->setData(index, SchMatrix::FrameTypes::Frame);
      animModel->setFrame(index.column());
      break;
    case SchMatrix::MenuEntry::RemoveFrame:
      animModel->removeData(index);
      break;
    case SchMatrix::MenuEntry::InsertKeyframe: {
      auto layer = animModel->getLayer(index.row());

      // Set data and check if current Keyframe is empty
      animModel->setData(index, (layer->currentKeyframe()->empty())
                                    ? SchMatrix::FrameTypes::BlankKey
                                    : SchMatrix::FrameTypes::Key);

      animModel->setFrame(index.column());
      break;
    }
    case SchMatrix::MenuEntry::InsertBlankKeyframe:
      animModel->setData(index, SchMatrix::FrameTypes::BlankKey);

      animModel->setFrame(index.column());
      break;
    case SchMatrix::MenuEntry::ClearFrames:
      break;
    case SchMatrix::MenuEntry::SelectAllFrames:
      int row = index.row();

      QModelIndex left = animModel->index(row, 0);
      QModelIndex right =
          animModel->index(row, animModel->elementCount(row) - 1);

      QItemSelection selection(left, right);
      selectionModel()->clear();
      selectionModel()->select(selection, QItemSelectionModel::Select);
      break;
  }

  auto layer = animModel->getLayer(index.row());

  qDebug() << layer->animations();
  for (auto l : layer->pauses()) {
    qDebug() << l << l->duration();
  }
}

void TimelineView::setModel(QAbstractItemModel *model) {
  if (!qobject_cast<SchMatrix::AnimationModel *>(model)) {
    qWarning() << tr(
        "SchMatrix::TimelineView::setModel cannot set invalid model");
    return;
  }

  QTableView::setModel(model);

  // Prevent invalid currentIndex at start
  // set value to layer 1, first blank keyframe
  setCurrentIndex(model->index(0, 0));

  if (model == animModel) return;

  if (animModel) {
    disconnect(animModel, SIGNAL(frameChanged(int, int)), this,
               SLOT(updateFrame(int, int)));
  }

  if (model) {
    animModel = static_cast<SchMatrix::AnimationModel *>(model);

    connect(animModel, SIGNAL(frameChanged(int, int)), this,
            SLOT(updateFrame(int, int)));
  }
}

void TimelineView::mouseMoveEvent(QMouseEvent *event) {
  QTableView::mouseMoveEvent(event);

  if (!(event->buttons() & Qt::LeftButton)) return;

  auto index = indexAt(event->pos());

  if (!index.isValid()) return;

  animModel->setFrame(index.column());
}

void TimelineView::updateFrame(int newFrame, int oldFrame) {
  qDebug() << "timeline updateFrame";

  QRegion r1(columnViewportPosition(newFrame), 0, columnWidth(0),
             viewport()->height());
  QRegion r2(columnViewportPosition(oldFrame), 0, columnWidth(0),
             viewport()->height());
  QRegion r3 = r2.united(r1);

  // Update player indicators
  viewport()->update(r3);
  header.viewport()->update();
}

}  // namespace SchMatrix

void SchMatrix::TimelineView::contextMenuEvent(QContextMenuEvent *event) {
  auto point = event->pos();

  if (!indexAt(point).isValid()) return;

  index = indexAt(point);

  timelineMenu.exec(event->globalPos());
}