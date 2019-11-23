#include "layer.h"

#include <QGraphicsScene>
#include "config.h"
#include "graphicswidget.h"
#include "keyframe.h"
#include "symbol.h"

namespace SchMatrix {

// parent is always rootAnimation(QParallelAnimationGroup)
Layer::Layer(QGraphicsScene *scene, QObject *parent, const QString &name,
             int zValue)
    : QSequentialAnimationGroup(parent), m_zValue(zValue), m_scene(scene) {
  setObjectName(name);
}

Layer::Layer(QObject *parent) : QSequentialAnimationGroup(parent) {}

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
  auto keyframe = qobject_cast<Keyframe *>(currentAnimation());

  if (keyframe) return keyframe;

  return nullptr;
}

Keyframe *Layer::nextKeyframe() const {
  auto idx = indexOfAnimation(currentAnimation());

  if (idx != animationCount() - 1)
    return qobject_cast<SchMatrix::Keyframe *>(animationAt(idx + 1));

  return nullptr;
}

Keyframe *Layer::prevKeyframe() const {
  auto idx = indexOfAnimation(currentAnimation());

  if (idx != 0)
    return qobject_cast<SchMatrix::Keyframe *>(animationAt(idx - 1));

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

int Layer::zValue() const { return m_zValue; };

void Layer::setZValue(const int &zValue) {
  m_zValue = zValue;

  // Update current items
  for (auto item : currentKeyframe()->objects()) {
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
  m_scene->addItem(item);
  currentKeyframe()->addObject(item);
}

void Layer::removeItem(GraphicsWidget *item) {
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

void Layer::deleteItem(GraphicsWidget *item) {
  currentKeyframe()->deleteObject(item);
}

void Layer::deleteKeyframe(Keyframe *keyframe) { delete keyframe; }

void Layer::addKeyframe(Keyframe *keyframe, int startFrame) {
  m_frameToKeyframe[startFrame] = keyframe;
  addAnimation(keyframe);
}

void Layer::insertKeyframe(int idx, Keyframe *keyframe, int startFrame) {
  auto currentKey = currentKeyframe();

  if (idx <= indexOfAnimation(currentKey)) {
    currentKey->setStartFrame(startFrame + 1);
    m_frameToKeyframe[startFrame + 1] = currentKey;
  }

  m_frameToKeyframe[startFrame] = keyframe;
  insertAnimation(idx, keyframe);
}

void Layer::updateFrameToKeyframe(SchMatrix::Keyframe *fromKeyframe) {
  auto keys = keyframes();
  auto keyEnd = fromKeyframe->endFrame();

  for (int i = keys.indexOf(fromKeyframe) + 1; i < keys.size(); ++i) {
    auto key = keys[i];

    m_frameToKeyframe.remove(key->startFrame());
    key->setStartFrame(keyEnd);
    m_frameToKeyframe[key->startFrame()] = key;
    keyEnd = key->endFrame();
  }
}

Keyframe *Layer::keyframeAtFrame(int frame) {
  auto it = m_frameToKeyframe.lowerBound(frame);

  if (it == m_frameToKeyframe.end()) return m_frameToKeyframe.last();

  if (it.key() > frame) return *--it;

  return *it;
}

Keyframe *Layer::keyframeAtMsec(int msec) {
  return keyframeAtFrame(msec / SchMatrix::frameLength);
}

void Layer::updateCurrentTime(int currentTime) {
  QSequentialAnimationGroup::updateCurrentTime(currentTime);

  auto keyframe = keyframeAtMsec(currentTime);
  auto items = keyframe->objects();

  if (m_lastKeyframe != keyframe) {
    // remove previous objects
    if (m_lastKeyframe)
      for (auto item : m_lastKeyframe->objects()) {
        m_scene->removeItem(item);
      }

    // add current objects
    for (auto item : items) {
      // Ensure correct zValue
      item->setZValue(m_zValue);
      m_scene->addItem(item);
    }

    m_lastKeyframe = keyframe;
  }

  if (!keyframe->empty()) {
    auto rootDuration =
        static_cast<QParallelAnimationGroup *>(parent())->duration();

    // Hide currentItems only if the layer is finished and it isn't at the end
    if (currentTime == duration() && currentTime != rootDuration) {
      for (auto item : items) {
        item->hide();
      }
    } else if (currentTime < duration()) {
      for (auto item : items) {
        item->show();
      }
    }
  }
}

}  // namespace SchMatrix
