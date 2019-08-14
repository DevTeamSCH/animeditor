#ifndef QGRAPHICSTEXTWIDGET_H
#define QGRAPHICSTEXTWIDGET_H

#include <QGraphicsTextItem>
#include "core_global.h"
#include "graphicswidget.h"

namespace SchMatrix {

class CORESHARED_EXPORT GraphicsTextWidget : public SchMatrix::GraphicsWidget {
  Q_OBJECT

 public:
  explicit GraphicsTextWidget(const QString &string, qreal x, qreal y,
                              QGraphicsItem *parent = nullptr,
                              Qt::WindowFlags wFlags = Qt::WindowFlags());
  explicit GraphicsTextWidget(const GraphicsTextWidget &other);

  enum { Type = SchMatrix::ItemTypes::Text };

  // QGraphicsItem interface
  int type() const override;

  // GraphicsWidget interface
  GraphicsWidget *clone() const override;

 private:
  QGraphicsTextItem m_text;
};

}  // namespace SchMatrix

#endif  // QGRAPHICSTEXTWIDGET_H
