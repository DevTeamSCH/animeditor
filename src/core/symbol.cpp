#include "symbol.h"

#include <QGraphicsItemGroup>
#include "layer.h"

namespace SchMatrix {

Symbol::Symbol(QGraphicsScene* scene, QGraphicsItem* parent)
    : SchMatrix::GraphicsWidget(parent), m_animationModel(scene, this) {}

Symbol::Symbol(const Symbol& other) : m_animationModel(other.m_animationModel) {
  copyProperties(other);
}

void Symbol::addItem(SchMatrix::GraphicsWidget* item) {
  m_animationModel.currentLayer()->addItem(item);
  item->setParentItem(this);
}

void Symbol::removeItem(SchMatrix::GraphicsWidget* item) {
  m_animationModel.currentLayer()->removeItem(item);
  item->setParentItem(nullptr);
}

AnimationModel* Symbol::animationModel() { return &m_animationModel; }

int Symbol::type() const { return Type; }

SchMatrix::GraphicsWidget* Symbol::clone() const { return new Symbol(*this); }

}  // namespace SchMatrix
