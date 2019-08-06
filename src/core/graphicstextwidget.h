#ifndef QGRAPHICSTEXTWIDGET_H
#define QGRAPHICSTEXTWIDGET_H

#include <QGraphicsTextItem>
#include "graphicswidget.h"

namespace SchMatrix {

class GraphicsTextWidget : public SchMatrix::GraphicsWidget {
  Q_OBJECT

 public:
  explicit GraphicsTextWidget(const QString &string,
                              QGraphicsItem *parent = nullptr,
                              Qt::WindowFlags wFlags = Qt::WindowFlags());

  enum { Type = SchMatrix::ItemTypes::Text };

  // QGraphicsItem interface
  int type() const override;

 private:
  QGraphicsTextItem text;
};

}  // namespace SchMatrix

#endif  // QGRAPHICSTEXTWIDGET_H
