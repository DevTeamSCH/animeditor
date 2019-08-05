#ifndef GRAPHICSWIDGET_H
#define GRAPHICSWIDGET_H

#include <QGraphicsWidget>
#include "core_global.h"

namespace SchMatrix {

class CORESHARED_EXPORT GraphicsWidget : public QGraphicsWidget {
  Q_OBJECT

 public:
  explicit GraphicsWidget(QGraphicsItem *parent = nullptr,
                          Qt::WindowFlags wFlags = Qt::WindowFlags());
};

}  // namespace SchMatrix

#endif  // GRAPHICSWIDGET_H
