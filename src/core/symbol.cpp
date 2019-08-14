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

Symbol::Symbol(const Symbol& other) : m_animationModel(other.m_animationModel) {
  copyProperties(other);

  auto rootAnim = m_animationModel.rootAnimation();

  for (int i = 0; i < rootAnim->animationCount(); ++i) {
    auto layer = static_cast<SchMatrix::Layer*>(rootAnim->animationAt(i));

    // Set layerItem
    auto layerItem = layer->layerItem();

    layerItem->setPos(mapFromItem(layerItem, 0, 0));
    layerItem->setParentItem(this);
  }
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

SchMatrix::GraphicsWidget* Symbol::clone() const { return new Symbol(*this); }

}  // namespace SchMatrix
