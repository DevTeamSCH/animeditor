#ifndef GRAPHICSRECTWIDGET_H
#define GRAPHICSRECTWIDGET_H

#include <QGraphicsRectItem>
#include "graphicswidget.h"

namespace SchMatrix {

class GraphicsRectWidget : public SchMatrix::GraphicsWidget {
  Q_OBJECT

 public:
  explicit GraphicsRectWidget(qreal x, qreal y, qreal width, qreal height,
                              QGraphicsItem *parent = nullptr,
                              Qt::WindowFlags wFlags = Qt::WindowFlags());

  enum { Type = SchMatrix::ItemTypes::Rectangle };

  // QGraphicsItem interface
  int type() const override;

  // GraphicsWidget interface
 protected:
  void strokeColorUpdate(const QColor &color) override;
  void fillColorUpdate(const QColor &color) override;

 private:
  QGraphicsRectItem rect;
};

}  // namespace SchMatrix

#endif  // GRAPHICSRECTWIDGET_H
