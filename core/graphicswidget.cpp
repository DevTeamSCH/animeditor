#include "graphicswidget.h"

namespace SchMatrix {

GraphicsWidget::GraphicsWidget(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QGraphicsWidget(parent, wFlags) {}

QColor GraphicsWidget::getStrokeColor() const { return strokeColor; }

void GraphicsWidget::setStrokeColor(const QColor &value) {
  strokeColor = value;
  emit strokeColorChanged(value);
}

QColor GraphicsWidget::getFillColor() const { return fillColor; }

void GraphicsWidget::setFillColor(const QColor &value) {
  fillColor = value;
  emit fillColorChanged(value);
}

}  // namespace SchMatrix
