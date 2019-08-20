#ifndef GRAPHICSOVALWIDGET_H
#define GRAPHICSOVALWIDGET_H

#include <QGraphicsEllipseItem>
#include "core_global.h"
#include "graphicswidget.h"

namespace SchMatrix {

class CORESHARED_EXPORT GraphicsOvalWidget : public SchMatrix::GraphicsWidget {
  Q_OBJECT

 public:
  explicit GraphicsOvalWidget(const QRectF &rect,
                              QGraphicsItem *parent = nullptr,
                              Qt::WindowFlags wFlags = Qt::WindowFlags());
  explicit GraphicsOvalWidget(qreal x, qreal y, qreal width, qreal height,
                              QGraphicsItem *parent = nullptr,
                              Qt::WindowFlags wFlags = Qt::WindowFlags());
  explicit GraphicsOvalWidget(QGraphicsItem *parent = nullptr,
                              Qt::WindowFlags wFlags = Qt::WindowFlags());
  explicit GraphicsOvalWidget(const GraphicsOvalWidget &other);

  enum { Type = SchMatrix::ItemTypes::Oval };

  // QGraphicsItem interface
  int type() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  int startAngle() const;
  void setStartAngle(int angle);
  int spanAngle() const;
  void setSpanAngle(int angle);
  QPainterPath shape() const override;

  // GraphicsWidget interface
  GraphicsWidget *clone() const override;

 private:
  int m_startAngle = 0;
  int m_spanAngle = 360 * 16;
};

}  // namespace SchMatrix

#endif  // GRAPHICSOVALWIDGET_H
