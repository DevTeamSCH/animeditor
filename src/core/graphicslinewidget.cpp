#include "graphicslinewidget.h"

#include <QPainter>

namespace SchMatrix {

GraphicsLineWidget::GraphicsLineWidget(qreal x1, qreal y1, qreal x2, qreal y2,
                                       QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags) {
  setGeometry(x1, y1, x2, y2);
}

GraphicsLineWidget::GraphicsLineWidget(const GraphicsLineWidget &other) {}

int GraphicsLineWidget::type() const { return Type; }

void SchMatrix::GraphicsLineWidget::paint(QPainter *painter,
                                          const QStyleOptionGraphicsItem *,
                                          QWidget *) {
  painter->setPen(m_strokeColor);

  auto rect = boundingRect();
  painter->drawLine(rect.topLeft(), rect.bottomRight());
}

GraphicsWidget *GraphicsLineWidget::clone() const {
  return new GraphicsLineWidget(*this);
}

}  // namespace SchMatrix
