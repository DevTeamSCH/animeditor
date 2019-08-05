#include "graphicswidget.h"

#include <QMetaProperty>

namespace SchMatrix {

GraphicsWidget::GraphicsWidget(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QGraphicsWidget(parent, wFlags) {
  // Set important flags
  setFlags(ItemIsMovable | ItemIsSelectable | ItemHasNoContents);
}

GraphicsWidget::GraphicsWidget(GraphicsWidget &other) {
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

  // Clone children
  auto items = other.childItems();
  if (items.count() == 0) return;

  for (auto item : items) {
    auto newItem = new GraphicsWidget(*static_cast<GraphicsWidget *>(item));
    newItem->setParentItem(this);
  }
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

void GraphicsWidget::strokeColorUpdate(const QColor &) {}

void GraphicsWidget::fillColorUpdate(const QColor &) {}

}  // namespace SchMatrix
