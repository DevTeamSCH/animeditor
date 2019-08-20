#ifndef GRAPHICSLINEWIDGET_H
#define GRAPHICSLINEWIDGET_H

#include <QGraphicsLineItem>
#include "core_global.h"
#include "graphicswidget.h"

namespace SchMatrix {

class CORESHARED_EXPORT GraphicsLineWidget : public SchMatrix::GraphicsWidget {
  Q_OBJECT

 public:
  explicit GraphicsLineWidget(QGraphicsItem *parent = nullptr,
                              Qt::WindowFlags wFlags = Qt::WindowFlags());
  explicit GraphicsLineWidget(const QLineF &line, QGraphicsItem *parent,
                              Qt::WindowFlags wFlags = Qt::WindowFlags());
  explicit GraphicsLineWidget(qreal x1, qreal y1, qreal x2, qreal y2,
                              QGraphicsItem *parent = nullptr,
                              Qt::WindowFlags wFlags = Qt::WindowFlags());
  explicit GraphicsLineWidget(const GraphicsLineWidget &other);

  enum { Type = SchMatrix::ItemTypes::Line };

  // QGraphicsItem interface
  int type() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  QRectF boundingRect() const override;
  QPainterPath shape() const override;

  // GraphicsWidget interface
  GraphicsWidget *clone() const override;

  QLineF line() const;
  void setLine(const QLineF &line);
  void setLine(qreal x1, qreal y1, qreal x2, qreal y2);

 private:
  QLineF m_line;
};

}  // namespace SchMatrix

#endif  // GRAPHICSLINEWIDGET_H
