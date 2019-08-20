#include "graphicslinewidget.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>

namespace SchMatrix {

GraphicsLineWidget::GraphicsLineWidget(QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags) {}

GraphicsLineWidget::GraphicsLineWidget(const QLineF &line,
                                       QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags) {
  setGeometry(line.x1(), line.y1(), line.x2(), line.y2());
  setLine(line);
}

GraphicsLineWidget::GraphicsLineWidget(qreal x1, qreal y1, qreal x2, qreal y2,
                                       QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags) {
  setGeometry(x1, y1, x2, y2);
  setLine(x1, y1, x2, y2);
}

GraphicsLineWidget::GraphicsLineWidget(const GraphicsLineWidget &other) {
  copyProperties(other);
}

int GraphicsLineWidget::type() const { return Type; }

void SchMatrix::GraphicsLineWidget::paint(QPainter *painter,
                                          const QStyleOptionGraphicsItem *,
                                          QWidget *) {
  painter->setPen(m_pen);
  painter->drawLine(m_line);
}

QRectF GraphicsLineWidget::boundingRect() const {
  if (m_pen.widthF() == 0.0) {
    const qreal x1 = m_line.p1().x();
    const qreal x2 = m_line.p2().x();
    const qreal y1 = m_line.p1().y();
    const qreal y2 = m_line.p2().y();
    qreal lx = qMin(x1, x2);
    qreal rx = qMax(x1, x2);
    qreal ty = qMin(y1, y2);
    qreal by = qMax(y1, y2);
    return QRectF(lx, ty, rx - lx, by - ty);
  }
  return shape().controlPointRect();
}

QPainterPath GraphicsLineWidget::shape() const {
  QPainterPath path;
  if (m_line == QLineF()) return path;

  path.moveTo(m_line.p1());
  path.lineTo(m_line.p2());
  return qt_graphicsItem_shapeFromPath(path, m_pen);
}

GraphicsWidget *GraphicsLineWidget::clone() const {
  return new GraphicsLineWidget(*this);
}

QLineF GraphicsLineWidget::line() const { return m_line; }

void GraphicsLineWidget::setLine(const QLineF &line) {
  if (m_line == line) return;
  prepareGeometryChange();
  m_line = line;
  update();
}

void GraphicsLineWidget::setLine(qreal x1, qreal y1, qreal x2, qreal y2) {
  setLine(QLineF(x1, y1, x2, y2));
}

}  // namespace SchMatrix
