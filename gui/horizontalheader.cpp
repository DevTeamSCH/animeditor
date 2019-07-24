#include "horizontalheader.h"

#include <QColor>
#include <QDebug>
#include <QPainter>
#include <QString>
#include <QTableView>
#include "animationmodel.h"
#include "config.h"

namespace SchMatrix {

HorizontalHeader::HorizontalHeader(QWidget *parent)
    : QHeaderView(Qt::Horizontal, parent), header(this) {
  setFixedHeight(60);
}

void HorizontalHeader::paintEvent(QPaintEvent *) {
  auto firstVisualColumn = visualIndexAt(0);
  auto lastVisualColumn = visualIndexAt(viewport()->width());

  if (firstVisualColumn == -1) firstVisualColumn = 0;
  if (lastVisualColumn == -1) lastVisualColumn = count() - 1;

  auto currentColumn =
      static_cast<SchMatrix::AnimationModel *>(model())->getCurrentFrame();
  auto table = static_cast<QTableView *>(parent());
  auto headerX = table->columnViewportPosition(currentColumn);

  QPainter painter(viewport());

  for (int i = firstVisualColumn; i <= lastVisualColumn; ++i) {
    auto posX = table->columnViewportPosition(i);
    auto cellHeight = header.height();

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

}  // namespace SchMatrix
