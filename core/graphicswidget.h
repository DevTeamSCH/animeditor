#ifndef GRAPHICSWIDGET_H
#define GRAPHICSWIDGET_H

#include <QColor>
#include <QGraphicsWidget>
#include "core_global.h"

namespace SchMatrix {

class CORESHARED_EXPORT GraphicsWidget : public QGraphicsWidget {
  Q_OBJECT
  Q_PROPERTY(QColor strokeColor READ getStrokeColor WRITE setStrokeColor NOTIFY
                 strokeColorChanged)
  Q_PROPERTY(QColor fillColor READ getFillColor WRITE setFillColor NOTIFY
                 fillColorChanged)

 public:
  explicit GraphicsWidget(QGraphicsItem *parent = nullptr,
                          Qt::WindowFlags wFlags = Qt::WindowFlags());

  QColor getStrokeColor() const;
  void setStrokeColor(const QColor &value);
  QColor getFillColor() const;
  void setFillColor(const QColor &value);

 signals:
  void strokeColorChanged(QColor color);
  void fillColorChanged(QColor color);

 protected:
  QColor strokeColor, fillColor;
};

}  // namespace SchMatrix

#endif  // GRAPHICSWIDGET_H
