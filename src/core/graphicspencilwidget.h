#ifndef QGRAPHICSPATHWIDGET_H
#define QGRAPHICSPATHWIDGET_H

#include <QGraphicsPathItem>
#include "core_global.h"
#include "graphicswidget.h"

namespace SchMatrix {

class CORESHARED_EXPORT GraphicsPathWidget : public SchMatrix::GraphicsWidget {
  Q_OBJECT

 public:
  explicit GraphicsPathWidget(const QPainterPath &path, qreal x, qreal y,
                              QGraphicsItem *parent = nullptr,
                              Qt::WindowFlags wFlags = Qt::WindowFlags());
  explicit GraphicsPathWidget(const GraphicsPathWidget &other);

  enum { Type = SchMatrix::ItemTypes::Pencil };

  // QGraphicsItem interface
  int type() const override;

  // GraphicsWidget interface
  GraphicsWidget *clone() const override;

 private:
  QGraphicsPathItem m_pathItem;
};

}  // namespace SchMatrix

#endif  // QGRAPHICSPATHWIDGET_H
