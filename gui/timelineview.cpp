#include "timelineview.h"

#include <QCursor>
#include <QDebug>
#include <QHeaderView>
#include <QModelIndex>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QScrollBar>
#include "config.h"
#include "framedelegate.h"

namespace SchMatrix {

TimelineView::TimelineView(QWidget *parent)
    : QTableView(parent), header(this), timelineMenu(this) {
  setHorizontalHeader(&header);
  setContextMenuPolicy(Qt::CustomContextMenu);
  setItemDelegate(new SchMatrix::FrameDelegate(this));

  connect(this, &QWidget::customContextMenuRequested, this,
          &TimelineView::handleMenuRequest);
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

  if (currentColumn < animModel->getLastFrame())
    posX += colWidth / 2;
  else
    posX -= colWidth / 2;

  QPainter painter(viewport());

  painter.setPen(Qt::red);
  painter.drawLine(posX, 0, posX, viewport()->height());
}

void TimelineView::mousePressEvent(QMouseEvent *event) {
  QTableView::mousePressEvent(event);

  auto index = indexAt(event->pos());

  if (!index.isValid()) return;

  animModel->setFrame(index.column());
  viewport()->update();
  header.viewport()->update();
}

void TimelineView::handleMenuRequest(const QPoint &idx) {
  if (!indexAt(idx).isValid()) return;

  index = indexAt(idx);

  animModel->setTime(SchMatrix::frameLength * indexAt(idx).column());

  timelineMenu.exec(QCursor::pos());
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

      // check if previous Keyframe is empty
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
  animModel = static_cast<SchMatrix::AnimationModel *>(model);
}

}  // namespace SchMatrix
