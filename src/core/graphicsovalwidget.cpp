#include "graphicsovalwidget.h"

#include <QPen>

namespace SchMatrix {

GraphicsOvalWidget::GraphicsOvalWidget(qreal x, qreal y, qreal width,
                                       qreal height, QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags),
      ellipse(x, y, width, height, this) {}

int GraphicsOvalWidget::type() const { return Type; }

void GraphicsOvalWidget::strokeColorUpdate(const QColor &color) {
  ellipse.setPen(color);
}

void GraphicsOvalWidget::fillColorUpdate(const QColor &color) {
  ellipse.setBrush(color);
}

}  // namespace SchMatrix
