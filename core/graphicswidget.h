#ifndef GRAPHICSWIDGET_H
#define GRAPHICSWIDGET_H

#include <QColor>
#include <QGraphicsWidget>
#include "core_global.h"

namespace SchMatrix {

enum ItemTypes {
  Text = QGraphicsItem::UserType,
  Line,
  Rectangle,
  Oval,
  Pencil
};

class CORESHARED_EXPORT GraphicsWidget : public QGraphicsWidget {
  Q_OBJECT
  Q_PROPERTY(QColor strokeColor READ getStrokeColor WRITE setStrokeColor NOTIFY
                 strokeColorChanged)
  Q_PROPERTY(QColor fillColor READ getFillColor WRITE setFillColor NOTIFY
                 fillColorChanged)

 public:
  explicit GraphicsWidget(QGraphicsItem *parent = nullptr,
                          Qt::WindowFlags wFlags = Qt::WindowFlags());
  explicit GraphicsWidget(GraphicsWidget &other);

  QColor getStrokeColor() const;
  void setStrokeColor(const QColor &value);
  QColor getFillColor() const;
  void setFillColor(const QColor &value);

 signals:
  void strokeColorChanged(QColor color);
  void fillColorChanged(QColor color);

 protected:
  virtual void strokeColorUpdate(const QColor &color);
  virtual void fillColorUpdate(const QColor &color);

  QColor strokeColor, fillColor;
};

}  // namespace SchMatrix

#endif  // GRAPHICSWIDGET_H
