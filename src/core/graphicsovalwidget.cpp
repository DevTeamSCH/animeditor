#include "graphicsovalwidget.h"

#include <QPainter>

namespace SchMatrix {

GraphicsOvalWidget::GraphicsOvalWidget(const QRectF &rect,
                                       QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags) {
  setGeometry(rect);
}

GraphicsOvalWidget::GraphicsOvalWidget(qreal x, qreal y, qreal width,
                                       qreal height, QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags) {
  setGeometry(x, y, width, height);
}

GraphicsOvalWidget::GraphicsOvalWidget(QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags) {}

GraphicsOvalWidget::GraphicsOvalWidget(const GraphicsOvalWidget &other) {
  copyProperties(other);
}

int GraphicsOvalWidget::type() const { return Type; }

void GraphicsOvalWidget::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *, QWidget *) {
  painter->setPen(m_pen);
  painter->setBrush(m_brush);
  auto rect = QGraphicsWidget::boundingRect();

  if ((m_spanAngle != 0) && (qAbs(m_spanAngle) % (360 * 16) == 0))
    painter->drawEllipse(rect);
  else
    painter->drawPie(rect, m_startAngle, m_spanAngle);
}

int GraphicsOvalWidget::startAngle() const { return m_startAngle; }

void GraphicsOvalWidget::setStartAngle(int angle) {
  if (angle != m_startAngle) {
    prepareGeometryChange();
    m_startAngle = angle;
    update();
  }
}

int GraphicsOvalWidget::spanAngle() const { return m_spanAngle; }

void GraphicsOvalWidget::setSpanAngle(int angle) {
  if (angle != m_spanAngle) {
    prepareGeometryChange();
    m_spanAngle = angle;
    update();
  }
}

QRectF GraphicsOvalWidget::boundingRect() const {
  return shape().controlPointRect();

  QRectF rect;
  qreal pw = pen().style() == Qt::NoPen ? qreal(0) : pen().widthF();
  if (pw == 0.0 && m_spanAngle == 360 * 16)
    rect = QGraphicsWidget::boundingRect();
  else
    rect = shape().controlPointRect();

  return rect;
}

QPainterPath GraphicsOvalWidget::shape() const {
  QPainterPath path;
  auto rect = QGraphicsWidget::boundingRect();
  if (rect.isNull()) return path;
  if (m_spanAngle != 360 * 16) {
    path.moveTo(rect.center());
    path.arcTo(rect, m_startAngle / 16.0, m_spanAngle / 16.0);
  } else {
    path.addEllipse(rect);
  }

  return qt_graphicsItem_shapeFromPath(path, m_pen);
}

GraphicsWidget *GraphicsOvalWidget::clone() const {
  return new GraphicsOvalWidget(*this);
}

}  // namespace SchMatrix
