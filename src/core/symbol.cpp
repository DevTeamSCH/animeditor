#include "symbol.h"

#include <QGraphicsItemGroup>
#include "layer.h"

namespace SchMatrix {

Symbol::Symbol(QList<QGraphicsWidget*> items, QGraphicsScene* scene,
               QGraphicsItem* parent)
    : QGraphicsWidget(parent), animModel(scene, this) {
  auto layer = animModel.currentLayer();
  layer->setGroupParent(this);

  for (auto i : items) {
    layer->addItem(i);
  }
}

Symbol::Symbol(QGraphicsWidget* item, QGraphicsScene* scene,
               QGraphicsItem* parent)
    : QGraphicsWidget(parent), animModel(scene, this) {
  auto layer = animModel.currentLayer();
  layer->setGroupParent(this);

  animModel.currentLayer()->addItem(item);
}

void Symbol::addItem(QGraphicsWidget* item) {
  animModel.currentLayer()->addItem(item);
}

void Symbol::removeItem(QGraphicsWidget* item) {
  animModel.currentLayer()->removeItem(item);
}

AnimationModel* Symbol::getAnimationModel() { return &animModel; }

}  // namespace SchMatrix
