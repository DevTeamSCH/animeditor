#include "graphicspathwidget.h"

#include <QPen>

namespace SchMatrix {

GraphicsPathWidget::GraphicsPathWidget(const QPainterPath &path, qreal x,
                                       qreal y, QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags), m_pathItem(path, this) {
  auto rect = m_pathItem.boundingRect();
  setGeometry(x, y, rect.width(), rect.height());
}

GraphicsPathWidget::GraphicsPathWidget(const GraphicsPathWidget &other) {
  copyProperties(other);

  auto &path = other.m_pathItem;
  m_pathItem.setParentItem(this);

  // Set item's properties
  m_pathItem.setPath(path.path());
}

int GraphicsPathWidget::type() const { return Type; }

GraphicsWidget *GraphicsPathWidget::clone() const {
  return new GraphicsPathWidget(*this);
}

void GraphicsPathWidget::strokeColorUpdate(const QColor &color) {
  m_pathItem.setPen(color);
}

void GraphicsPathWidget::fillColorUpdate(const QColor &color) {
  m_pathItem.setBrush(color);
}

}  // namespace SchMatrix
