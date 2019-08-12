#include "horizontalheader.h"

#include <QColor>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QRegion>
#include <QString>
#include "animationmodel.h"
#include "config.h"

namespace SchMatrix {

HorizontalHeader::HorizontalHeader(QWidget *parent)
    : QHeaderView(Qt::Horizontal, parent),
      m_headerControls(this),
      m_timelineView(static_cast<QTableView *>(parent)) {
  setFixedHeight(60);
  setSectionResizeMode(QHeaderView::Fixed);
  viewport()->setMouseTracking(false);
}

void HorizontalHeader::paintEvent(QPaintEvent *) {
  auto firstVisualColumn = visualIndexAt(0);
  auto lastVisualColumn = visualIndexAt(viewport()->width());

  if (firstVisualColumn == -1) firstVisualColumn = 0;
  if (lastVisualColumn == -1) lastVisualColumn = count() - 1;

  auto currentColumn = m_animationModel->currentFrame();
  auto headerX = m_timelineView->columnViewportPosition(currentColumn);

  QPainter painter(viewport());

  for (int i = firstVisualColumn; i <= lastVisualColumn; ++i) {
    auto posX = m_timelineView->columnViewportPosition(i);
    auto cellHeight = m_headerControls.height();

    // FPS and second indicator
    if ((i + 1) % SchMatrix::fps == 0) {
      painter.save();
      painter.setPen(Qt::NoPen);
      painter.setBrush(QColor("#e0e0e0"));
      painter.drawRect(posX, cellHeight, sectionSize(0), cellHeight);
      painter.restore();

      painter.drawText(posX, height() - 19,
                       QString::number((i + 1) / SchMatrix::fps) + "s");
    }

    // Frame length indicator
    painter.drawLine(posX, height() - 3, posX, height());

    // Frame number indicator every 5 frames
    if ((i + 1) % 5 == 0 || i == 0)
      painter.drawText(posX + 1, height() - 3,
                       QString::number((!i) ? 1 : i + 1));
  }

  // Player head
  painter.setPen(Qt::red);
  painter.setBrush(QColor("#80ff0000"));
  painter.drawRect(headerX, 29, sectionSize(0), 30);
}

void HorizontalHeader::resizeEvent(QResizeEvent *event) {
  QHeaderView::resizeEvent(event);

  m_headerControls.setFixedWidth(width());
}

void HorizontalHeader::setModel(QAbstractItemModel *model) {
  QHeaderView::setModel(model);

  if (model == m_animationModel) return;

  // skip default model
  if (!qobject_cast<SchMatrix::AnimationModel *>(model)) return;

  if (model) {
    m_animationModel = static_cast<SchMatrix::AnimationModel *>(model);
    m_headerControls.setModel(m_animationModel);
    viewport()->update();
  }
}

// Only for communicaton between controls and this widget
void HorizontalHeader::updateFrame(int newFrame, int oldFrame) {
  QRegion r1(m_timelineView->columnViewportPosition(newFrame), 0,
             defaultSectionSize(), m_timelineView->viewport()->height());
  QRegion r2(m_timelineView->columnViewportPosition(oldFrame), 0,
             defaultSectionSize(), m_timelineView->viewport()->height());
  QRegion r3 = r2.united(r1);

  auto firstVisualColumn = visualIndexAt(0);
  auto lastVisualColumn = visualIndexAt(viewport()->width());

  if (firstVisualColumn == -1) firstVisualColumn = 0;
  if (lastVisualColumn == -1) lastVisualColumn = count() - 1;

  auto itemCount = lastVisualColumn - firstVisualColumn - 1;

  // Update player indicators
  viewport()->update();
  m_timelineView->viewport()->update(r3);

  if (newFrame >= lastVisualColumn) {
    auto col = (newFrame + itemCount > count() - 1) ? count() - 1
                                                    : newFrame + itemCount;
    m_timelineView->scrollTo(
        m_animationModel->index(m_animationModel->currentLayerIdx(), col));
  }

  if (newFrame <= firstVisualColumn) {
    auto col = (newFrame - itemCount < 0) ? 0 : newFrame - itemCount;
    m_timelineView->scrollTo(
        m_animationModel->index(m_animationModel->currentLayerIdx(), col));
  }
}

void HorizontalHeader::mouseMoveEvent(QMouseEvent *event) {
  if (!(event->buttons() & Qt::LeftButton)) return;

  m_animationModel->setFrame(logicalIndexAt(event->pos()));
}

void SchMatrix::HorizontalHeader::mousePressEvent(QMouseEvent *event) {
  if (!(event->buttons() & Qt::LeftButton)) return;

  m_animationModel->setFrame(logicalIndexAt(event->pos()));
}

}  // namespace SchMatrix
