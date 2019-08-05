#include "graphicspathwidget.h"

#include <QPen>

namespace SchMatrix {

GraphicsPathWidget::GraphicsPathWidget(const QPainterPath &path,
                                       QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags), pathItem(path, this) {}

int GraphicsPathWidget::type() const { return Type; }

void GraphicsPathWidget::strokeColorUpdate(const QColor &color) {
  pathItem.setPen(color);
}

void GraphicsPathWidget::fillColorUpdate(const QColor &color) {
  pathItem.setBrush(color);
}

}  // namespace SchMatrix
