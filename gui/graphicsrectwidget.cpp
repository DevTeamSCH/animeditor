#include "graphicsrectwidget.h"

#include <QPen>

namespace SchMatrix {
GraphicsRectWidget::GraphicsRectWidget(qreal x, qreal y, qreal width,
                                       qreal height, QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags),
      rect(x, y, width, height, this) {}

int GraphicsRectWidget::type() const { return Type; }

void GraphicsRectWidget::strokeColorUpdate(const QColor &color) {
  rect.setPen(color);
}

void GraphicsRectWidget::fillColorUpdate(const QColor &color) {
  rect.setBrush(color);
}

}  // namespace SchMatrix
