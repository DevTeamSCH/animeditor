#include "graphicswidget.h"

#include <QMetaProperty>
#include "graphicslinewidget.h"
#include "graphicsovalwidget.h"
#include "graphicspathwidget.h"
#include "graphicsrectwidget.h"
#include "graphicstextwidget.h"

namespace SchMatrix {

GraphicsWidget::GraphicsWidget(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QGraphicsWidget(parent, wFlags) {
  // Set important flags
  setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
}

QColor GraphicsWidget::getStrokeColor() const { return m_strokeColor; }

void GraphicsWidget::setStrokeColor(const QColor &value) {
  m_strokeColor = value;
  strokeColorUpdate(value);
  emit strokeColorChanged(value);
}

QColor GraphicsWidget::getFillColor() const { return m_fillColor; }

void GraphicsWidget::setFillColor(const QColor &value) {
  m_fillColor = value;
  fillColorUpdate(value);
  emit fillColorChanged(value);
}

GraphicsWidget *GraphicsWidget::Create(ItemTypes type, qreal x, qreal y,
                                       qreal width, qreal height) {
  if (type == ItemTypes::Line)
    return new SchMatrix::GraphicsLineWidget(x, y, width, height);
  if (type == ItemTypes::Oval)
    return new SchMatrix::GraphicsOvalWidget(x, y, width, height);
  if (type == ItemTypes::Text)
    return new SchMatrix::GraphicsTextWidget(tr("INSERT TEXT HERE"), x, y);
  if (type == ItemTypes::Pencil)
    return new SchMatrix::GraphicsPathWidget(QPainterPath(), x, y);
  if (type == ItemTypes::Rectangle)
    return new SchMatrix::GraphicsRectWidget(x, y, width, height);

  return nullptr;
}

void GraphicsWidget::copyProperties(const GraphicsWidget &other) {
  auto metaobject = other.metaObject();

  // Set all properties including base class
  for (int i = 0; i < metaobject->propertyCount(); ++i) {
    auto name = metaobject->property(i).name();
    QString string(name);

    // Skip invalid or unwanted properties
    if (string == "children" || string == "layout" || string == "parent" ||
        string == "effect")
      continue;

    setProperty(name, other.property(name));
  }
}

void GraphicsWidget::strokeColorUpdate(const QColor &) {}

void GraphicsWidget::fillColorUpdate(const QColor &) {}

}  // namespace SchMatrix
