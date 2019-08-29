#include "graphicspencilwidget.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPen>
#include <QSettings>
#include <QtMath>

namespace SchMatrix {

GraphicsPencilWidget::GraphicsPencilWidget(qreal x, qreal y, int width,
                                           int height, const QPixmap &pixmap,
                                           QGraphicsItem *parent,
                                           Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags), m_pixmapItem(pixmap, this) {
  m_pixmapItem.setFlag(ItemStacksBehindParent);

  auto rect = m_pixmapItem.boundingRect();

  if (pixmap.isNull()) {
    if (width == 0) width = SchMatrix::width;
    if (height == 0) height = SchMatrix::height;

    m_image = QImage(width, height, QImage::Format_RGBA8888);
    m_image.fill(Qt::white);
    m_pixmapItem.setPixmap(QPixmap::fromImage(m_image));

    setGeometry(x, y, width, height);
  } else {
    m_image = pixmap.toImage().convertToFormat(QImage::Format_RGBA8888);
    setGeometry(x, y, rect.width(), rect.height());
  }

  // Grid
  for (int row = 1; row < size().height(); ++row) {
    m_gridLines << QLine(0, row, size().width(), row);
  }

  for (int col = 1; col < size().width(); ++col) {
    m_gridLines << QLine(col, 0, col, size().height());
  }
}

GraphicsPencilWidget::GraphicsPencilWidget(const GraphicsPencilWidget &other) {
  copyProperties(other);

  auto &path = other.m_pixmapItem;
  m_pixmapItem.setParentItem(this);

  // Set item's properties
  m_pixmapItem.setPixmap(other.m_pixmapItem.pixmap());
}

int GraphicsPencilWidget::type() const { return Type; }

void GraphicsPencilWidget::paint(QPainter *painter,
                                 const QStyleOptionGraphicsItem *option,
                                 QWidget *widget) {
  painter->setPen(QPen(Qt::black, 0));
  painter->drawLines(m_gridLines);
}

GraphicsWidget *GraphicsPencilWidget::clone() const {
  return new GraphicsPencilWidget(*this);
}

void GraphicsPencilWidget::setDrawingEnabled(bool drawingEnabled) {
  m_drawingEnabled = drawingEnabled;
}

void GraphicsPencilWidget::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  if (m_drawingEnabled == false) {
    GraphicsWidget::mousePressEvent(event);
    return;
  }

  auto pos = event->pos();

  if (pos.x() >= size().width() || pos.y() >= size().height() ||
      !(event->buttons() & Qt::LeftButton))
    return;

  QSettings settings;
  m_image.setPixelColor(qFloor(pos.x()), qFloor(pos.y()),
                        settings.value("MainWindow/penColor").value<QColor>());
  m_pixmapItem.setPixmap(QPixmap::fromImage(m_image));
}

void GraphicsPencilWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  if (m_drawingEnabled == false) {
    GraphicsWidget::mouseMoveEvent(event);
    return;
  }

  auto pos = event->pos();
  QSettings settings;

  if (!boundingRect().contains(pos) || pos.x() >= size().width() ||
      pos.y() >= size().height() || !(event->buttons() & Qt::LeftButton))
    return;

  m_image.setPixelColor(qFloor(pos.x()), qFloor(pos.y()),
                        settings.value("MainWindow/penColor").value<QColor>());
  m_pixmapItem.setPixmap(QPixmap::fromImage(m_image));
}

}  // namespace SchMatrix
