#include "graphicsovalwidget.h"

#include <QPainter>

namespace SchMatrix {

GraphicsOvalWidget::GraphicsOvalWidget(qreal x, qreal y, qreal width,
                                       qreal height, QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags) {
  setGeometry(x, y, width, height);
}

GraphicsOvalWidget::GraphicsOvalWidget(const GraphicsOvalWidget &other) {
  copyProperties(other);
}

int GraphicsOvalWidget::type() const { return Type; }

void GraphicsOvalWidget::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *, QWidget *) {
  painter->setPen(m_strokeColor);
  painter->setBrush(m_fillColor);

  painter->drawEllipse(boundingRect());
}

GraphicsWidget *GraphicsOvalWidget::clone() const {
  return new GraphicsOvalWidget(*this);
}

void GraphicsOvalWidget::strokeColorUpdate(const QColor &color) {
  m_strokeColor = color;
}

void GraphicsOvalWidget::fillColorUpdate(const QColor &color) {
  m_fillColor = color;
}

}  // namespace SchMatrix
