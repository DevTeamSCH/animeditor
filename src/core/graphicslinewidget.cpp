#include "graphicslinewidget.h"

#include <QPen>

namespace SchMatrix {

GraphicsLineWidget::GraphicsLineWidget(qreal x1, qreal y1, qreal x2, qreal y2,
                                       QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags), m_line(x1, y1, x2, y2, this) {
  m_line.setPen(QPen(Qt::black, 1));
  auto rect = m_line.boundingRect();

  setGeometry(x1, y1, rect.width(), rect.height());
}

GraphicsLineWidget::GraphicsLineWidget(const GraphicsLineWidget &other) {
  copyProperties(other);

  auto &line = other.m_line;
  m_line.setParentItem(this);

  // Set item's properties
  m_line.setPen(line.pen());
  m_line.setLine(line.line());
}

int GraphicsLineWidget::type() const { return Type; }

GraphicsWidget *GraphicsLineWidget::clone() const {
  return new GraphicsLineWidget(*this);
}

void GraphicsLineWidget::strokeColorUpdate(const QColor &color) {
  m_line.setPen(QPen(color, 1));
}

}  // namespace SchMatrix
