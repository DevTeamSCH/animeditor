#include "graphicstextwidget.h"

#include <QGraphicsSceneMouseEvent>
#include "keyframe.h"

namespace SchMatrix {

GraphicsTextWidget::GraphicsTextWidget(const QString &string, qreal x, qreal y,
                                       QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags), m_text(string, this) {
  m_text.setFlag(ItemStacksBehindParent);

  auto rect = m_text.boundingRect();
  setGeometry(x, y, rect.width(), rect.height());
}

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

void GraphicsTextWidget::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  QGraphicsWidget::mousePressEvent(event);

  if (m_text.textInteractionFlags() & Qt::TextEditorInteraction) {
    event->ignore();
  }
}

QVariant GraphicsTextWidget::itemChange(

    QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
  // Editing is finished
  if (change == ItemSelectedHasChanged && value.toBool() == false) {
    m_text.setTextInteractionFlags(Qt::NoTextInteraction);
    resize(m_text.boundingRect().size());
  }

  return SchMatrix::GraphicsWidget::itemChange(change, value);
}

void GraphicsTextWidget::updatePen() {
  m_text.setDefaultTextColor(m_pen.color());
}

}  // namespace SchMatrix
