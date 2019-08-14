#include "graphicsovalwidget.h"

#include <QPen>

namespace SchMatrix {

GraphicsOvalWidget::GraphicsOvalWidget(qreal x, qreal y, qreal width,
                                       qreal height, QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags),
      m_ellipse(0, 0, width, height, this) {
  setGeometry(x, y, width, height);
}

GraphicsOvalWidget::GraphicsOvalWidget(const GraphicsOvalWidget &other) {
  copyProperties(other);

  auto &ellipse = other.m_ellipse;
  m_ellipse.setParentItem(this);

  // Set item's properties
  m_ellipse.setBrush(ellipse.brush());
  m_ellipse.setRect(ellipse.rect());
  m_ellipse.setPen(ellipse.pen());
}

int GraphicsOvalWidget::type() const { return Type; }

GraphicsWidget *GraphicsOvalWidget::clone() const {
  return new GraphicsOvalWidget(*this);
}

void GraphicsOvalWidget::strokeColorUpdate(const QColor &color) {
  m_ellipse.setPen(color);
}

void GraphicsOvalWidget::fillColorUpdate(const QColor &color) {
  m_ellipse.setBrush(color);
}

}  // namespace SchMatrix
