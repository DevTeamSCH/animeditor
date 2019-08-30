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

  // Without default image
  if (pixmap.isNull()) {
    if (width == 0) width = SchMatrix::width;
    if (height == 0) height = SchMatrix::height;

    // Item should not be moveable when created at 0, 0
    if (qRound(x) == 0 && qRound(y) == 0) setFlag(ItemIsMovable, false);

    m_image = QImage(width, height, QImage::Format_RGBA8888);
    m_image.fill(Qt::white);
    m_pixmapItem.setPixmap(QPixmap::fromImage(m_image));

    setGeometry(x, y, width, height);
  } else {  // With default image
    m_image = pixmap.toImage().convertToFormat(QImage::Format_RGBA8888);
    setGeometry(x, y, rect.width(), rect.height());
  }

  // Generate default grid
  for (int row = 1; row < size().height(); ++row) {
    m_gridLines << QLine(0, row, qRound(size().width()), row);
  }

  for (int col = 1; col < size().width(); ++col) {
    m_gridLines << QLine(col, 0, col, qRound(size().height()));
  }
}

GraphicsPencilWidget::GraphicsPencilWidget(const GraphicsPencilWidget &other) {
  copyProperties(other);

  auto &pixmapItem = other.m_pixmapItem;
  m_pixmapItem.setParentItem(this);

  m_image = other.m_image;
  m_gridLines = other.m_gridLines;
  m_drawingEnabled = false;
  m_gridEnabled = false;

  // Set item's properties
  m_pixmapItem.setPixmap(pixmapItem.pixmap());
  m_pixmapItem.setFlag(ItemStacksBehindParent);
}

int GraphicsPencilWidget::type() const { return Type; }

void GraphicsPencilWidget::paint(QPainter *painter,
                                 const QStyleOptionGraphicsItem *option,
                                 QWidget *widget) {
  painter->setPen(QPen(Qt::black, 0));

  if (m_gridEnabled) painter->drawLines(m_gridLines);
}

GraphicsWidget *GraphicsPencilWidget::clone() const {
  return new GraphicsPencilWidget(*this);
}

void GraphicsPencilWidget::setDrawingEnabled(bool drawingEnabled) {
  m_drawingEnabled = drawingEnabled;

  if (m_drawingEnabled == false) {
    m_gridEnabled = false;
  } else {
    m_gridEnabled = true;
  }

  update();
}

void GraphicsPencilWidget::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  if (m_drawingEnabled == false) {
    GraphicsWidget::mousePressEvent(event);
    return;
  }

  auto pos = event->pos();

  if (pos.x() >= size().width() || pos.y() >= size().height() ||
      (!(event->buttons() & Qt::LeftButton) &&
       !(event->buttons() & Qt::RightButton)))
    return;

  QSettings settings;

  if (event->buttons() & Qt::LeftButton) {
    m_pen.setColor(settings.value("MainWindow/penColor").value<QColor>());
    m_image.setPixelColor(qFloor(pos.x()), qFloor(pos.y()), m_pen.color());
  }

  if (event->buttons() & Qt::RightButton) {
    m_brush.setColor(settings.value("MainWindow/brushColor").value<QColor>());
    m_image.setPixelColor(qFloor(pos.x()), qFloor(pos.y()), m_brush.color());
  }

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
      pos.y() >= size().height() ||
      (!(event->buttons() & Qt::LeftButton) &&
       !(event->buttons() & Qt::RightButton)))
    return;

  if (event->buttons() & Qt::LeftButton)
    m_image.setPixelColor(qFloor(pos.x()), qFloor(pos.y()), m_pen.color());

  if (event->buttons() & Qt::RightButton)
    m_image.setPixelColor(qFloor(pos.x()), qFloor(pos.y()), m_brush.color());

  m_pixmapItem.setPixmap(QPixmap::fromImage(m_image));
}

bool GraphicsPencilWidget::gridEnabled() const { return m_gridEnabled; }

void GraphicsPencilWidget::setGridEnabled(bool gridEnabled) {
  m_gridEnabled = gridEnabled;
  update();
}

}  // namespace SchMatrix
