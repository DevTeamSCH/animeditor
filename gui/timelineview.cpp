#include "timelineview.h"

#include <QDebug>
#include <QHeaderView>
#include <QModelIndex>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QScrollBar>

namespace SchMatrix {

TimelineView::TimelineView(QWidget *parent) : QTableView(parent), header(this) {
  setHorizontalHeader(&header);
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
