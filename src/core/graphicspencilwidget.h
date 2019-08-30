#ifndef QGRAPHICSPATHWIDGET_H
#define QGRAPHICSPATHWIDGET_H

#include <QGraphicsPixmapItem>
#include <QImage>
#include "config.h"
#include "core_global.h"
#include "graphicswidget.h"

namespace SchMatrix {

class CORESHARED_EXPORT GraphicsPencilWidget
    : public SchMatrix::GraphicsWidget {
  Q_OBJECT
  Q_PROPERTY(bool gridEnabled READ gridEnabled WRITE setGridEnabled)

 public:
  explicit GraphicsPencilWidget(qreal x, qreal y, int width = SchMatrix::width,
                                int height = SchMatrix::height,
                                const QPixmap &pixmap = QPixmap(),
                                QGraphicsItem *parent = nullptr,
                                Qt::WindowFlags wFlags = Qt::WindowFlags());
  explicit GraphicsPencilWidget(const GraphicsPencilWidget &other);

  enum { Type = SchMatrix::ItemTypes::Pencil };

  // QGraphicsItem interface
  int type() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

  // GraphicsWidget interface
  GraphicsWidget *clone() const override;

  void setDrawingEnabled(bool drawingEnabled);

  bool gridEnabled() const;
  void setGridEnabled(bool gridEnabled);

  // QGraphicsItem interface
 protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

 private:
  QGraphicsPixmapItem m_pixmapItem;
  QImage m_image;
  QVector<QLine> m_gridLines;
  bool m_drawingEnabled = false;
  bool m_gridEnabled = true;
};

}  // namespace SchMatrix

#endif  // QGRAPHICSPATHWIDGET_H
