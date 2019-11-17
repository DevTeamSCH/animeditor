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
    : QTableView(parent), m_horizontalHeader(this), m_timelineMenu(this) {
  setHorizontalHeader(&m_horizontalHeader);
  setItemDelegate(new SchMatrix::FrameDelegate(this));

  connect(&m_timelineMenu, &QMenu::triggered, this, &TimelineView::handleMenu);
}

void TimelineView::paintEvent(QPaintEvent *event) {
  qDebug() << "timeline paint" << event->rect();

  // use default render
  QTableView::paintEvent(event);

  // use custom render
  auto firstVisualColumn = horizontalHeader()->visualIndexAt(0);
  auto lastVisualColumn = horizontalHeader()->visualIndexAt(
      horizontalHeader()->viewport()->width());

  if (firstVisualColumn == -1) firstVisualColumn = 0;
  if (lastVisualColumn == -1)
    lastVisualColumn = horizontalHeader()->count() - 1;

  auto currentColumn = m_animationModel->currentFrame();

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

  if (!(event->buttons() & Qt::LeftButton)) return;

  auto index = indexAt(event->pos());

  if (!index.isValid()) return;

  // Set current layer by index
  m_animationModel->setCurrentLayer(index.row());

  m_animationModel->setFrame(index.column());
}

void TimelineView::handleMenu(QAction *action) {
  switch (action->data().toInt()) {
    case SchMatrix::MenuEntry::CreateClassicTween:
      m_animationModel->createClassicTween();
      break;
    case SchMatrix::MenuEntry::InsertFrame:
      m_animationModel->setData(m_menuIndex, SchMatrix::FrameTypes::Frame);
      m_animationModel->setFrame(m_menuIndex.column());
      break;
    case SchMatrix::MenuEntry::RemoveFrame:
      m_animationModel->removeData(m_menuIndex);
      break;
    case SchMatrix::MenuEntry::InsertKeyframe: {
      // Set data and check if current Keyframe is empty
      m_animationModel->setData(m_menuIndex, SchMatrix::FrameTypes::Key);
      m_animationModel->setFrame(m_menuIndex.column());
      break;
    }
    case SchMatrix::MenuEntry::InsertBlankKeyframe:
      m_animationModel->setData(m_menuIndex, SchMatrix::FrameTypes::BlankKey);

      m_animationModel->setFrame(m_menuIndex.column());
      break;
    case SchMatrix::MenuEntry::ClearFrames:
      break;
    case SchMatrix::MenuEntry::SelectAllFrames:
      int row = m_menuIndex.row();

      QModelIndex left = m_animationModel->index(row, 0);
      QModelIndex right =
          m_animationModel->index(row, m_animationModel->rowSize(row) - 1);

      QItemSelection selection(left, right);
      selectionModel()->clear();
      selectionModel()->select(selection, QItemSelectionModel::Select);
      break;
  }

  auto layer = m_animationModel->layerAt(m_menuIndex.row());

  qDebug() << layer->animations();
  for (auto a : layer->animations()) {
    qDebug() << a << a->duration();
  }
}

void TimelineView::setModel(QAbstractItemModel *model) {
  auto animationModel = qobject_cast<SchMatrix::AnimationModel *>(model);

  if (!animationModel) {
    qWarning() << tr(
        "SchMatrix::TimelineView::setModel cannot set invalid model");
    return;
  }

  QTableView::setModel(model);

  // Prevent invalid currentIndex at start
  // set value to layer 1, first blank keyframe
  setCurrentIndex(model->index(0, 0));

  if (model == m_animationModel) return;

  if (m_animationModel) {
    disconnect(m_animationModel, SIGNAL(frameChanged(int, int)), this,
               SLOT(updateFrame(int, int)));
  }

  if (model) {
    m_animationModel = animationModel;

    connect(m_animationModel, SIGNAL(frameChanged(int, int)), this,
            SLOT(updateFrame(int, int)));
  }
}

void TimelineView::mouseMoveEvent(QMouseEvent *event) {
  QTableView::mouseMoveEvent(event);

  if (!(event->buttons() & Qt::LeftButton)) return;

  auto index = indexAt(event->pos());

  if (!index.isValid()) return;

  m_animationModel->setFrame(index.column());
}

void TimelineView::updateFrame(int newFrame, int oldFrame) {
  qDebug() << "timeline updateFrame";

  QRegion r1(columnViewportPosition(newFrame), 0, columnWidth(0),
             viewport()->height());
  QRegion r2(columnViewportPosition(oldFrame), 0, columnWidth(0),
             viewport()->height());
  QRegion r3 = r2.united(r1);

  auto firstVisualColumn = m_horizontalHeader.visualIndexAt(0);
  auto lastVisualColumn = m_horizontalHeader.visualIndexAt(viewport()->width());

  if (firstVisualColumn == -1) firstVisualColumn = 0;
  if (lastVisualColumn == -1) lastVisualColumn = m_horizontalHeader.count() - 1;

  auto itemCount = lastVisualColumn - firstVisualColumn - 1;

  // Update player indicators
  viewport()->update(r3);
  m_horizontalHeader.viewport()->update();

  // Don't scroll if menu was requested
  if (m_menuRequested == true) {
    m_menuRequested = false;
    return;
  }

  if (newFrame >= lastVisualColumn) {
    auto col = (newFrame + itemCount > m_horizontalHeader.count() - 1)
                   ? m_horizontalHeader.count() - 1
                   : newFrame + itemCount;
    scrollTo(m_animationModel->index(m_animationModel->currentLayerIdx(), col));
  }

  if (newFrame <= firstVisualColumn) {
    auto col = (newFrame - itemCount < 0) ? 0 : newFrame - itemCount;
    scrollTo(m_animationModel->index(m_animationModel->currentLayerIdx(), col));
  }
}

}  // namespace SchMatrix

void SchMatrix::TimelineView::contextMenuEvent(QContextMenuEvent *event) {
  auto point = event->pos();

  if (!indexAt(point).isValid()) return;

  m_menuIndex = indexAt(point);
  m_menuRequested = true;

  auto mouseEvent = QMouseEvent(QEvent::MouseButtonPress, event->pos(),
                                Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
  mousePressEvent(&mouseEvent);

  m_timelineMenu.exec(event->globalPos());
}
