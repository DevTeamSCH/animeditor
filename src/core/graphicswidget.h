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

class Keyframe;

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

  SchMatrix::Keyframe *currentKeyframe() const;
  void setCurrentKeyframe(SchMatrix::Keyframe *currentKeyframe);

  bool editing() const;
  void setEditing(bool editing);

 protected:
  QBrush m_brush;
  QPen m_pen;
  SchMatrix::Keyframe *m_currentKeyframe = nullptr;
  bool m_editing = false;

  // QGraphicsItem interface
  QVariant itemChange(GraphicsItemChange change,
                      const QVariant &value) override;

  // QGraphicsWidget interface
  void resizeEvent(QGraphicsSceneResizeEvent *event) override;
};

}  // namespace SchMatrix

#endif  // GRAPHICSWIDGET_H
