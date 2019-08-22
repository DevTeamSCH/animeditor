#include "graphicsrectwidget.h"

#include <QPainter>

namespace SchMatrix {
GraphicsRectWidget::GraphicsRectWidget(const QRectF &rect,
                                       QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags) {
  setGeometry(rect);
}

GraphicsRectWidget::GraphicsRectWidget(qreal x, qreal y, qreal width,
                                       qreal height, QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags) {
  setGeometry(x, y, width, height);
}

GraphicsRectWidget::GraphicsRectWidget(QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags) {}

GraphicsRectWidget::GraphicsRectWidget(const GraphicsRectWidget &other) {
  copyProperties(other);
}

int GraphicsRectWidget::type() const { return Type; }

void GraphicsRectWidget::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *, QWidget *) {
  painter->setPen(m_pen);
  painter->setBrush(Qt::cyan);
  painter->drawRect(QGraphicsWidget::boundingRect());
}

QRectF GraphicsRectWidget::boundingRect() const {
  qreal halfpw = pen().style() == Qt::NoPen ? qreal(0) : pen().widthF() / 2;
  auto rect = QGraphicsWidget::boundingRect();
  if (halfpw > 0.0) rect.adjust(-halfpw, -halfpw, halfpw, halfpw);

  return rect;
}

QPainterPath GraphicsRectWidget::shape() const {
  QPainterPath path;
  path.addRect(boundingRect());
  return qt_graphicsItem_shapeFromPath(path, m_pen);
}

GraphicsWidget *SchMatrix::GraphicsRectWidget::clone() const {
  return new GraphicsRectWidget(*this);
}

}  // namespace SchMatrix
