#include "symbol.h"

namespace SchMatrix {

Symbol::Symbol(QList<QGraphicsWidget*> items, QGraphicsScene* scene,
               QGraphicsItem* parent)
    : QGraphicsWidget(parent), animModel(scene, this), itemGroup(this) {
  for (auto i : items) {
    itemGroup.addToGroup(i);
  }
}

Symbol::Symbol(QGraphicsWidget* item, QGraphicsScene* scene,
               QGraphicsItem* parent)
    : QGraphicsWidget(parent), animModel(scene, this), itemGroup(this) {
  itemGroup.addToGroup(item);
}

Symbol::~Symbol() {
  for (auto i : itemGroup.childItems()) {
    itemGroup.removeFromGroup(i);
  }
}

void Symbol::addItem(QGraphicsWidget* item) { itemGroup.addToGroup(item); }

void Symbol::removeItem(QGraphicsWidget* item) {
  itemGroup.removeFromGroup(item);
}

QList<QGraphicsWidget*> Symbol::items() {
  QList<QGraphicsWidget*> list;

  for (auto i : itemGroup.childItems()) {
    list.append(static_cast<QGraphicsWidget*>(i));
  }

  return list;
}

AnimationModel* Symbol::getAnimationModel() { return &animModel; }

}  // namespace SchMatrix
