#ifndef QGRAPHICSPATHWIDGET_H
#define QGRAPHICSPATHWIDGET_H

#include <QGraphicsPathItem>
#include "core_global.h"
#include "graphicswidget.h"

namespace SchMatrix {

class CORESHARED_EXPORT GraphicsPathWidget : public SchMatrix::GraphicsWidget {
  Q_OBJECT

 public:
  explicit GraphicsPathWidget(const QPainterPath &path,
                              QGraphicsItem *parent = nullptr,
                              Qt::WindowFlags wFlags = Qt::WindowFlags());

  enum { Type = SchMatrix::ItemTypes::Pencil };

  // QGraphicsItem interface
  int type() const override;

  // GraphicsWidget interface
 protected:
  void strokeColorUpdate(const QColor &color) override;
  void fillColorUpdate(const QColor &color) override;

 private:
  QGraphicsPathItem pathItem;
};

}  // namespace SchMatrix

#endif  // QGRAPHICSPATHWIDGET_H
