#ifndef GRAPHICSWIDGET_H
#define GRAPHICSWIDGET_H

#include <QBrush>
#include <QGraphicsWidget>
#include <QPen>
#include "core_global.h"

namespace SchMatrix {

enum ItemTypes {
  Text = QGraphicsItem::UserType,
  Line,
  Rectangle,
  Oval,
  Pencil,
  SymbolItem
};

class CORESHARED_EXPORT GraphicsWidget : public QGraphicsWidget {
  Q_OBJECT
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QBrush brush READ brush WRITE setBrush)

 public:
  explicit GraphicsWidget(QGraphicsItem *parent = nullptr,
                          Qt::WindowFlags wFlags = Qt::WindowFlags());

  QPen pen() const;
  void setPen(const QPen &pen);
  QBrush brush() const;
  void setBrush(const QBrush &brush);

  static GraphicsWidget *Create(ItemTypes type, qreal x, qreal y, qreal width,
                                qreal height);
  virtual GraphicsWidget *clone() const = 0;
  void copyProperties(const GraphicsWidget &other);

  // Set automatically the transform point to the center
  void setUpdateTransformOriginPoint(bool enabled);

  // QGraphicsItem interface
  static QPainterPath qt_graphicsItem_shapeFromPath(const QPainterPath &path,
                                                    const QPen &pen);

 protected:
  QBrush m_brush;
  QPen m_pen = QPen(Qt::black, 0);  // https://doc.qt.io/qt-5/qpen.html#setWidth

  virtual void updatePen();
  virtual void updateBrush();

};

}  // namespace SchMatrix

#endif  // GRAPHICSWIDGET_H
