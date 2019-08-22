#ifndef GRAPHICSRECTWIDGET_H
#define GRAPHICSRECTWIDGET_H

#include <QGraphicsRectItem>
#include "core_global.h"
#include "graphicswidget.h"

namespace SchMatrix {

class CORESHARED_EXPORT GraphicsRectWidget : public SchMatrix::GraphicsWidget {
  Q_OBJECT

 public:
  explicit GraphicsRectWidget(const QRectF &rect,
                              QGraphicsItem *parent = nullptr,
                              Qt::WindowFlags wFlags = Qt::WindowFlags());
  explicit GraphicsRectWidget(qreal x, qreal y, qreal width, qreal height,
                              QGraphicsItem *parent = nullptr,
                              Qt::WindowFlags wFlags = Qt::WindowFlags());
  explicit GraphicsRectWidget(QGraphicsItem *parent = nullptr,
                              Qt::WindowFlags wFlags = Qt::WindowFlags());
  explicit GraphicsRectWidget(const GraphicsRectWidget &other);

  enum { Type = SchMatrix::ItemTypes::Rectangle };

  // QGraphicsItem interface
  int type() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  QRectF boundingRect() const override;
  QPainterPath shape() const override;

  // GraphicsWidget interface
  GraphicsWidget *clone() const override;
};

}  // namespace SchMatrix

#endif  // GRAPHICSRECTWIDGET_H
