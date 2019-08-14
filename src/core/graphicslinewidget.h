#ifndef GRAPHICSLINEWIDGET_H
#define GRAPHICSLINEWIDGET_H

#include <QGraphicsLineItem>
#include "core_global.h"
#include "graphicswidget.h"

namespace SchMatrix {

class CORESHARED_EXPORT GraphicsLineWidget : public SchMatrix::GraphicsWidget {
  Q_OBJECT

 public:
  explicit GraphicsLineWidget(qreal x1, qreal y1, qreal x2, qreal y2,
                              QGraphicsItem *parent = nullptr,
                              Qt::WindowFlags wFlags = Qt::WindowFlags());
  explicit GraphicsLineWidget(const GraphicsLineWidget &other);

  enum { Type = SchMatrix::ItemTypes::Line };

  // QGraphicsItem interface
  int type() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

  // GraphicsWidget interface
  GraphicsWidget *clone() const override;
};

}  // namespace SchMatrix

#endif  // GRAPHICSLINEWIDGET_H
