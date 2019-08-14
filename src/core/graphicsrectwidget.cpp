#include "graphicsrectwidget.h"

#include <QPainter>

namespace SchMatrix {
GraphicsRectWidget::GraphicsRectWidget(qreal x, qreal y, qreal width,
                                       qreal height, QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags) {
  setGeometry(x, y, width, height);
}

GraphicsRectWidget::GraphicsRectWidget(const GraphicsRectWidget &other) {
  copyProperties(other);
}

int GraphicsRectWidget::type() const { return Type; }

void GraphicsRectWidget::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *, QWidget *) {
  painter->setPen(m_strokeColor);
  painter->setBrush(m_fillColor);

  painter->drawRect(boundingRect());
}

GraphicsWidget *SchMatrix::GraphicsRectWidget::clone() const {
  return new GraphicsRectWidget(*this);
}

void GraphicsRectWidget::strokeColorUpdate(const QColor &color) {
  m_strokeColor = color;
}

void GraphicsRectWidget::fillColorUpdate(const QColor &color) {
  m_fillColor = color;
}

}  // namespace SchMatrix
