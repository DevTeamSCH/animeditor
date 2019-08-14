#include "graphicsrectwidget.h"

#include <QPen>

namespace SchMatrix {
GraphicsRectWidget::GraphicsRectWidget(qreal x, qreal y, qreal width,
                                       qreal height, QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags),
      m_rect(0, 0, width, height, this) {
  setGeometry(x, y, width, height);
}

GraphicsRectWidget::GraphicsRectWidget(const GraphicsRectWidget &other) {
  copyProperties(other);

  auto &rect = other.m_rect;
  m_rect.setParentItem(this);

  // Set item's properties
  m_rect.setPen(rect.pen());
  m_rect.setBrush(rect.brush());
  m_rect.setRect(rect.rect());
}

int GraphicsRectWidget::type() const { return Type; }

GraphicsWidget *SchMatrix::GraphicsRectWidget::clone() const {
  return new GraphicsRectWidget(*this);
}

void GraphicsRectWidget::strokeColorUpdate(const QColor &color) {
  m_rect.setPen(color);
}

void GraphicsRectWidget::fillColorUpdate(const QColor &color) {
  m_rect.setBrush(color);
}

}  // namespace SchMatrix
