#ifndef QGRAPHICSTEXTWIDGET_H
#define QGRAPHICSTEXTWIDGET_H

#include <QGraphicsTextItem>
#include "core_global.h"
#include "graphicswidget.h"

namespace SchMatrix {

class CORESHARED_EXPORT GraphicsTextWidget : public SchMatrix::GraphicsWidget {
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
