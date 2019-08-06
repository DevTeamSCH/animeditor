#include "symbol.h"

#include <QGraphicsItemGroup>
#include "layer.h"

namespace SchMatrix {

Symbol::Symbol(QList<QGraphicsWidget*> items, QGraphicsScene* scene,
               QGraphicsItem* parent)
    : QGraphicsWidget(parent), m_animationModel(scene, this) {
  auto layer = m_animationModel.currentLayer();
  layer->setGroupParent(this);

  for (auto i : items) {
    layer->addItem(i);
  }
}

Symbol::Symbol(QGraphicsWidget* item, QGraphicsScene* scene,
               QGraphicsItem* parent)
    : QGraphicsWidget(parent), m_animationModel(scene, this) {
  auto layer = m_animationModel.currentLayer();
  layer->setGroupParent(this);

  m_animationModel.currentLayer()->addItem(item);
}

void Symbol::addItem(QGraphicsWidget* item) {
  m_animationModel.currentLayer()->addItem(item);
}

void Symbol::removeItem(QGraphicsWidget* item) {
  m_animationModel.currentLayer()->removeItem(item);
}

AnimationModel* Symbol::animationModel() { return &m_animationModel; }

}  // namespace SchMatrix
