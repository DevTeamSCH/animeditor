#ifndef GRAPHICSRECTWIDGET_H
#define GRAPHICSRECTWIDGET_H

#include <QGraphicsRectItem>
#include "core_global.h"
#include "graphicswidget.h"

namespace SchMatrix {

class CORESHARED_EXPORT GraphicsRectWidget : public SchMatrix::GraphicsWidget {
  Q_OBJECT

 public:
  explicit GraphicsRectWidget(qreal x, qreal y, qreal width, qreal height,
                              QGraphicsItem *parent = nullptr,
                              Qt::WindowFlags wFlags = Qt::WindowFlags());
  explicit GraphicsRectWidget(const GraphicsRectWidget &other);

  enum { Type = SchMatrix::ItemTypes::Rectangle };

  // QGraphicsItem interface
  int type() const override;

  // GraphicsWidget interface
  GraphicsWidget *clone() const override;

  // GraphicsWidget interface
 protected:
  void strokeColorUpdate(const QColor &color) override;
  void fillColorUpdate(const QColor &color) override;

 private:
  QGraphicsRectItem m_rect;
};

}  // namespace SchMatrix

#endif  // GRAPHICSRECTWIDGET_H
