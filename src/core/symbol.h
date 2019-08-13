#ifndef SYMBOL_H
#define SYMBOL_H

#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QList>
#include "animationmodel.h"
#include "core_global.h"
#include "graphicswidget.h"

namespace SchMatrix {

class CORESHARED_EXPORT Symbol : public SchMatrix::GraphicsWidget {
  Q_OBJECT

 public:
  explicit Symbol(QList<SchMatrix::GraphicsWidget*> items, QGraphicsScene*,
                  QGraphicsItem* parent = nullptr);
  explicit Symbol(SchMatrix::GraphicsWidget* item, QGraphicsScene*,
                  QGraphicsItem* parent = nullptr);

  void addItem(SchMatrix::GraphicsWidget* item);
  void removeItem(SchMatrix::GraphicsWidget* item);
  void configureLayerItem(QGraphicsItemGroup* layerItem = nullptr);

  AnimationModel* animationModel();

 private:
  AnimationModel m_animationModel;
};

}  // namespace SchMatrix

#endif  // SYMBOL_H
