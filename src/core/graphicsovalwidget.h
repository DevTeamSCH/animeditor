#ifndef GRAPHICSOVALWIDGET_H
#define GRAPHICSOVALWIDGET_H

#include <QGraphicsEllipseItem>
#include "core_global.h"
#include "graphicswidget.h"

namespace SchMatrix {

class CORESHARED_EXPORT GraphicsOvalWidget : public SchMatrix::GraphicsWidget {
  Q_OBJECT

 public:
  explicit GraphicsOvalWidget(qreal x, qreal y, qreal width, qreal height,
                              QGraphicsItem *parent = nullptr,
                              Qt::WindowFlags wFlags = Qt::WindowFlags());
  explicit GraphicsOvalWidget(const GraphicsOvalWidget &other);

  enum { Type = SchMatrix::ItemTypes::Oval };

  // QGraphicsItem interface
  int type() const override;

  // GraphicsWidget interface
  GraphicsWidget *clone() const override;

  // GraphicsWidget interface
 protected:
  void strokeColorUpdate(const QColor &color) override;
  void fillColorUpdate(const QColor &color) override;

 private:
  QGraphicsEllipseItem m_ellipse;
};

}  // namespace SchMatrix

#endif  // GRAPHICSOVALWIDGET_H
