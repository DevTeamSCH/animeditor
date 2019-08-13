#include "symbol.h"

#include <QGraphicsItemGroup>
#include "layer.h"

namespace SchMatrix {

Symbol::Symbol(QList<SchMatrix::GraphicsWidget*> items, QGraphicsScene* scene,
               QGraphicsItem* parent)
    : SchMatrix::GraphicsWidget(parent), m_animationModel(scene, this) {
  auto layer = m_animationModel.currentLayer();

  for (auto i : items) {
    layer->addItem(i);
  }

  configureLayerItem();
}

Symbol::Symbol(SchMatrix::GraphicsWidget* item, QGraphicsScene* scene,
               QGraphicsItem* parent)
    : SchMatrix::GraphicsWidget(parent), m_animationModel(scene, this) {
  m_animationModel.currentLayer()->addItem(item);

  configureLayerItem();
}

void Symbol::addItem(SchMatrix::GraphicsWidget* item) {
  m_animationModel.currentLayer()->addItem(item);
}

void Symbol::removeItem(SchMatrix::GraphicsWidget* item) {
  m_animationModel.currentLayer()->removeItem(item);
}

void Symbol::configureLayerItem(QGraphicsItemGroup* layerItem) {
  if (!layerItem) layerItem = m_animationModel.currentLayer()->layerItem();

  setGeometry(layerItem->boundingRect());

  layerItem->setPos(mapFromItem(layerItem, 0, 0));
  layerItem->setParentItem(this);
}

AnimationModel* Symbol::animationModel() { return &m_animationModel; }

int Symbol::type() const { return Type; }

}  // namespace SchMatrix
