#include "layer.h"

#include <QGraphicsScene>
#include <QList>
#include "config.h"
#include "graphicswidget.h"
#include "keyframe.h"
#include "layer.h"
#include "symbol.h"

namespace SchMatrix {

// parent is always rootAnimation(QParallelAnimationGroup)
Layer::Layer(QGraphicsScene *scene, QObject *parent, const QString &name,
             int zValue)
    : QSequentialAnimationGroup(parent), m_zValue(zValue), m_scene(scene) {
  setObjectName(name);

  connect(this, &QSequentialAnimationGroup::currentAnimationChanged, this,
          &Layer::updateLayer);
}

// Set parent after construction
Layer::Layer(const Layer &other)
    : Layer(other.m_scene, nullptr, other.objectName(), other.m_zValue) {
  // Clone everything
  for (int i = 0; i < other.animationCount(); ++i) {
    auto anim = other.animationAt(i);

    auto keyframe = qobject_cast<SchMatrix::Keyframe *>(anim);

    if (keyframe) {
      auto newKeyframe = new SchMatrix::Keyframe(*keyframe);

      addAnimation(newKeyframe);
    } else {  // pause
      addPause(anim->duration());
    }
  }
}

QList<QAbstractAnimation *> Layer::animations() const {
  QList<QAbstractAnimation *> anims;

  for (int i = 0; i < animationCount(); ++i) {
    anims.append(animationAt(i));
  }

  return anims;
}

QList<QPauseAnimation *> Layer::pauses() const {
  QList<QPauseAnimation *> pauseAnims;

  for (int i = 0; i < animationCount(); ++i) {
    auto pause = qobject_cast<QPauseAnimation *>(animationAt(i));

    if (pause) pauseAnims.append(pause);
  }

  return pauseAnims;
}

QList<Keyframe *> Layer::keyframes() const {
  QList<Keyframe *> keyframes;

  for (int i = 0; i < animationCount(); ++i) {
    auto anim = animationAt(i);
    if (qobject_cast<Keyframe *>(anim))
      keyframes.append(static_cast<Keyframe *>(anim));
  }

  return keyframes;
}

Keyframe *Layer::currentKeyframe() const {
  auto currentAnim = currentAnimation();
  auto keyframe = qobject_cast<Keyframe *>(currentAnimation());

  if (keyframe) return keyframe;

  // currentAnimation is a pause
  // before a pause there is always a keyframe
  if (animationCount() > 1)
    return static_cast<Keyframe *>(
        animationAt(indexOfAnimation(currentAnim) - 1));

  return nullptr;
}

Keyframe *Layer::nextKeyframe() const {
  if (animationCount() < 2) return nullptr;

  auto keys = keyframes();
  auto idx = keys.indexOf(currentKeyframe());

  if (idx == keys.size() - 1) return nullptr;

  return keys[idx + 1];
}

Keyframe *Layer::prevKeyframe() const {
  if (animationCount() < 2) return nullptr;

  auto keys = keyframes();
  auto keyframe = currentKeyframe();
  auto currentAnim = qobject_cast<SchMatrix::Keyframe *>(currentAnimation());
  auto idx = keys.indexOf(keyframe);

  // anim is pause
  if (!currentAnim) return keyframe;

  // anim is (blank)keyframe
  if (idx != 0) return keys[idx - 1];

  return nullptr;
}

int Layer::animFramePosition(QAbstractAnimation *anim) const {
  auto animIdx = indexOfAnimation(anim);
  int frames = 0;

  for (int i = 0; i < animIdx; ++i) {
    frames += animationAt(i)->duration() / SchMatrix::frameLength;
  }

  return frames;
}

QPauseAnimation *Layer::currentPause() const {
  return qobject_cast<QPauseAnimation *>(currentAnimation());
}

int Layer::zValue() const { return m_zValue; };

void Layer::setZValue(const int &zValue) {
  m_zValue = zValue;

  // Update current items
  for (auto item : m_currentItems) {
    item->setZValue(zValue);
  }
}

QAbstractAnimation *Layer::animationAtMsec(int msec) const {
  if (msec <= 0) return animationAt(0);
  if (msec >= duration()) return animationAt(animationCount() - 1);

  int dur = 0;

  for (auto i : animations()) {
    dur += i->duration();

    if (msec < dur) return i;
  }

  return nullptr;
}

void Layer::addItem(GraphicsWidget *item) {
  m_currentItems << item;
  m_scene->addItem(item);
  currentKeyframe()->addObject(item);
}

void Layer::removeItem(GraphicsWidget *item) {
  m_currentItems.removeAll(item);
  m_scene->removeItem(item);
  currentKeyframe()->removeObject(item);
}

Symbol *Layer::convertToSymbol(const QList<GraphicsWidget *> &items) {
  // Clean items from current layer and keyframe
  for (auto item : items) {
    removeItem(item);
  }

  // Add items to Symbol
  auto symbol = new Symbol(m_scene);

  // Add symbol to current keyframe
  addItem(symbol);

  return symbol;
}

// Note: this function will be called for all the animations before/after the
// current animation
void Layer::updateLayer(QAbstractAnimation *current) {
  // Skip unwanted animations and pauses
  if (current != animationAtMsec(currentTime())) return;

  auto keyframe = (!qobject_cast<Keyframe *>(current))
                      ? currentKeyframe()
                      : static_cast<Keyframe *>(current);

  // Skip invalid and same keyframe before pause
  if (keyframe == m_lastKeyframe || !keyframe) return;

  m_lastKeyframe = keyframe;

  // remove previous objects
  for (auto item : m_currentItems) {
    m_scene->removeItem(item);
  }
  m_currentItems.clear();

  // skip blank keyframe
  if (keyframe->animationCount() == 1) return;

  // add current objects
  for (auto item : keyframe->objects()) {
    m_currentItems << item;

    // Ensure correct zValue
    item->setZValue(m_zValue);
    m_scene->addItem(item);
  }
}

void Layer::updateCurrentTime(int currentTime) {
  QSequentialAnimationGroup::updateCurrentTime(currentTime);

  auto rootDuration =
      static_cast<QParallelAnimationGroup *>(parent())->duration();

  // Hide layerItem only if the layer is finished and it isn't at the end
  if (currentTime == duration() && currentTime != rootDuration) {
    for (auto item : m_currentItems) {
      item->hide();
    }
  } else if (currentTime < duration()) {
    for (auto item : m_currentItems) {
      item->show();
    }
  }
}

}  // namespace SchMatrix
