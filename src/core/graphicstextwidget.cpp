#include "graphicstextwidget.h"

#include <QGraphicsSceneMouseEvent>
#include "keyframe.h"

namespace SchMatrix {

GraphicsTextWidget::GraphicsTextWidget(const QString &string, qreal x, qreal y,
                                       QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags), m_text(string, this) {
  auto rect = m_text.boundingRect();
  setGeometry(x, y, rect.width(), rect.height());
}

GraphicsTextWidget::GraphicsTextWidget(QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags) {}

GraphicsTextWidget::GraphicsTextWidget(const GraphicsTextWidget &other) {
  copyProperties(other);

  auto &text = other.m_text;
  m_text.setParentItem(this);

  // Set item's properties
  m_text.setTextInteractionFlags(Qt::NoTextInteraction);
  m_text.setPlainText(text.toPlainText());
}

int GraphicsTextWidget::type() const { return Type; }

GraphicsWidget *GraphicsTextWidget::clone() const {
  return new GraphicsTextWidget(*this);
}

QGraphicsTextItem &GraphicsTextWidget::textItem() { return m_text; }

void GraphicsTextWidget::updatePen() {
  m_text.setDefaultTextColor(m_pen.color());
}

}  // namespace SchMatrix
