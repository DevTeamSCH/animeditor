#ifndef GRAPHICSLINEWIDGET_H
#define GRAPHICSLINEWIDGET_H

#include <QGraphicsLineItem>
#include "graphicswidget.h"

namespace SchMatrix {

class GraphicsLineWidget : public SchMatrix::GraphicsWidget {
  Q_OBJECT

 public:
  explicit GraphicsLineWidget(qreal x1, qreal y1, qreal x2, qreal y2,
                              QGraphicsItem *parent = nullptr,
                              Qt::WindowFlags wFlags = Qt::WindowFlags());

  enum { Type = SchMatrix::ItemTypes::Line };

  // QGraphicsItem interface
  int type() const override;

  // GraphicsWidget interface
 protected:
  void strokeColorUpdate(const QColor &color) override;

 private:
  QGraphicsLineItem line;
};

}  // namespace SchMatrix

#endif  // GRAPHICSLINEWIDGET_H
