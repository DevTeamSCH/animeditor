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
  setFlags(ItemIsMovable | ItemIsSelectable | ItemHasNoContents);
}

QColor GraphicsWidget::getStrokeColor() const { return strokeColor; }

void GraphicsWidget::setStrokeColor(const QColor &value) {
  strokeColor = value;
  strokeColorUpdate(value);
  emit strokeColorChanged(value);
}

QColor GraphicsWidget::getFillColor() const { return fillColor; }

void GraphicsWidget::setFillColor(const QColor &value) {
  fillColor = value;
  fillColorUpdate(value);
  emit fillColorChanged(value);
}

GraphicsWidget *GraphicsWidget::Create(ItemTypes type) {
  if (type == ItemTypes::Line) new SchMatrix::GraphicsLineWidget(0, 0, 0, 0);
  if (type == ItemTypes::Oval) new SchMatrix::GraphicsOvalWidget(0, 0, 0, 0);
  if (type == ItemTypes::Text)
    new SchMatrix::GraphicsTextWidget(tr("INSERT TEXT HERE"));
  if (type == ItemTypes::Pencil)
    new SchMatrix::GraphicsPathWidget(QPainterPath());
  if (type == ItemTypes::Rectangle)
    new SchMatrix::GraphicsRectWidget(0, 0, 0, 0);

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
