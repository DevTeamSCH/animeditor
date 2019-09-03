#include "graphicswidget.h"

#include <QMetaProperty>
#include "graphicslinewidget.h"
#include "graphicsovalwidget.h"
#include "graphicspencilwidget.h"
#include "graphicsrectwidget.h"
#include "graphicstextwidget.h"

namespace SchMatrix {

GraphicsWidget::GraphicsWidget(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QGraphicsWidget(parent, wFlags) {
  // Set important flags
  setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
}

QPen GraphicsWidget::pen() const { return m_pen; }

void GraphicsWidget::setPen(const QPen &pen) {
  if (m_pen == pen) return;
  prepareGeometryChange();
  m_pen = pen;
  updatePen();
  update();
}

QBrush GraphicsWidget::brush() const { return m_brush; }

void GraphicsWidget::setBrush(const QBrush &brush) {
  if (m_brush == brush) return;
  m_brush = brush;
  updateBrush();
  update();
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
    return new SchMatrix::GraphicsPencilWidget(x, y, width, height);
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

void GraphicsWidget::setUpdateTransformOriginPoint(bool enabled) {
  if (enabled)
    connect(this, &GraphicsWidget::geometryChanged, this,
            [=]() { setTransformOriginPoint(boundingRect().center()); });
  else
    disconnect(this, &GraphicsWidget::geometryChanged, nullptr, nullptr);
}

QPainterPath GraphicsWidget::qt_graphicsItem_shapeFromPath(
    const QPainterPath &path, const QPen &pen) {
  const qreal penWidthZero = qreal(0.00000001);

  if (path == QPainterPath() || pen == Qt::NoPen) return path;
  QPainterPathStroker ps;
  ps.setCapStyle(pen.capStyle());
  if (pen.widthF() <= 0.0)
    ps.setWidth(penWidthZero);
  else
    ps.setWidth(pen.widthF());
  ps.setJoinStyle(pen.joinStyle());
  ps.setMiterLimit(pen.miterLimit());
  QPainterPath p = ps.createStroke(path);
  p.addPath(path);
  return p;
}

void GraphicsWidget::updatePen() {}

void GraphicsWidget::updateBrush() {}

}  // namespace SchMatrix
