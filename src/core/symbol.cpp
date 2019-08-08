#include "symbol.h"

#include <QGraphicsItemGroup>
#include "layer.h"

namespace SchMatrix {

Symbol::Symbol(QList<QGraphicsWidget*> items, QGraphicsScene* scene,
               QGraphicsItem* parent)
    : QGraphicsWidget(parent), m_animationModel(scene, this) {
  auto layer = m_animationModel.currentLayer();

  for (auto i : items) {
    layer->addItem(i);
  }

  configureLayerItem();
}

Symbol::Symbol(QGraphicsWidget* item, QGraphicsScene* scene,
               QGraphicsItem* parent)
    : QGraphicsWidget(parent), m_animationModel(scene, this) {
  m_animationModel.currentLayer()->addItem(item);

  configureLayerItem();
}

void Symbol::addItem(QGraphicsWidget* item) {
  m_animationModel.currentLayer()->addItem(item);
}

void Symbol::removeItem(QGraphicsWidget* item) {
  m_animationModel.currentLayer()->removeItem(item);
}

void Symbol::configureLayerItem(QGraphicsItemGroup* layerItem) {
  if (!layerItem) layerItem = m_animationModel.currentLayer()->layerItem();

  setGeometry(layerItem->boundingRect());

  layerItem->setPos(mapFromItem(layerItem, 0, 0));
  layerItem->setParentItem(this);
}

AnimationModel* Symbol::animationModel() { return &m_animationModel; }

}  // namespace SchMatrix
