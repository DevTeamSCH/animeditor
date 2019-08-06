#include "symbol.h"

#include <QGraphicsItemGroup>
#include "layer.h"

namespace SchMatrix {

Symbol::Symbol(QList<QGraphicsWidget*> items, QGraphicsScene* scene,
               QGraphicsItem* parent)
    : QGraphicsWidget(parent), animModel(scene, this) {
  auto layer = animModel.getCurrentLayer();
  layer->setGroupParent(this);

  for (auto i : items) {
    layer->addItem(i);
  }
}

Symbol::Symbol(QGraphicsWidget* item, QGraphicsScene* scene,
               QGraphicsItem* parent)
    : QGraphicsWidget(parent), animModel(scene, this) {
  auto layer = animModel.getCurrentLayer();
  layer->setGroupParent(this);

  animModel.getCurrentLayer()->addItem(item);
}

void Symbol::addItem(QGraphicsWidget* item) {
  animModel.getCurrentLayer()->addItem(item);
}

void Symbol::removeItem(QGraphicsWidget* item) {
  animModel.getCurrentLayer()->removeItem(item);
}

AnimationModel* Symbol::getAnimationModel() { return &animModel; }

}  // namespace SchMatrix
