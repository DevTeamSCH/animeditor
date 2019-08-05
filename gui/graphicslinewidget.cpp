#include "graphicslinewidget.h"

#include <QPen>

namespace SchMatrix {

GraphicsLineWidget::GraphicsLineWidget(qreal x1, qreal y1, qreal x2, qreal y2,
                                       QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags), line(x1, y1, x2, y2, this) {
  line.setPen(QPen(Qt::black, 1));
}

int GraphicsLineWidget::type() const { return Type; }

void GraphicsLineWidget::strokeColorUpdate(const QColor &color) {
  line.setPen(QPen(color, 1));
}

}  // namespace SchMatrix
