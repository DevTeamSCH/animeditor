#include "graphicstextwidget.h"

namespace SchMatrix {

GraphicsTextWidget::GraphicsTextWidget(const QString &string, qreal x, qreal y,
                                       QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags), m_text(string, this) {
  m_text.setTextInteractionFlags(Qt::TextEditorInteraction);

  auto rect = m_text.boundingRect();
  setGeometry(x, y, rect.width(), rect.height());
}

GraphicsTextWidget::GraphicsTextWidget(const GraphicsTextWidget &other) {
  copyProperties(other);

  auto &text = other.m_text;
  m_text.setParentItem(this);

  // Set item's properties
  m_text.setTextInteractionFlags(Qt::TextEditorInteraction);
  m_text.setPlainText(text.toPlainText());
}

int GraphicsTextWidget::type() const { return Type; }

GraphicsWidget *GraphicsTextWidget::clone() const {
  return new GraphicsTextWidget(*this);
}

}  // namespace SchMatrix
