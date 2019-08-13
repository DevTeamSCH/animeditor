#include "layer.h"

#include <QGraphicsScene>
#include <QList>
#include "config.h"
#include "graphicswidget.h"
#include "keyframe.h"
#include "layer.h"
#include "symbol.h"

namespace SchMatrix {

Layer::Layer(QGraphicsScene *scene, QObject *parent, const QString &name,
             int zValue)
    : QSequentialAnimationGroup(parent),
      m_zValue(zValue),
      m_lastKeyframe(nullptr) {
  setObjectName(name);
  scene->addItem(&m_layerItem);
  m_layerItem.setZValue(zValue);

  connect(this, &QSequentialAnimationGroup::currentAnimationChanged, this,
          &Layer::updateLayer);
}

Layer::~Layer() {
  // QGraphicsItemGroup must not delete items
  for (auto i : m_layerItem.childItems()) {
    m_layerItem.removeFromGroup(i);
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
  m_layerItem.setZValue(zValue);
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
  m_layerItem.addToGroup(item);
  currentKeyframe()->addObject(item);
}

void Layer::removeItem(GraphicsWidget *item) {
  m_layerItem.removeFromGroup(item);
  currentKeyframe()->removeObject(item);
}

const QGraphicsItemGroup *Layer::layerItem() const { return &m_layerItem; }

QGraphicsItemGroup *Layer::layerItem() { return &m_layerItem; }

Symbol *Layer::convertToSymbol(const QList<GraphicsWidget *> &items) {
  // Clean items from current layer and keyframe
  for (auto item : items) {
    removeItem(item);
  }

  // Add items to Symbol
  auto symbol = new Symbol(items, m_layerItem.scene());

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
  for (auto item : m_layerItem.childItems()) {
    m_layerItem.removeFromGroup(item);
    m_layerItem.scene()->removeItem(item);
  }

  // skip blank keyframe
  if (keyframe->animationCount() == 1) return;

  // add current objects
  for (auto item : keyframe->objects()) {
    m_layerItem.addToGroup(item);
  }

  m_layerItem.scene()->update();
}

void Layer::updateCurrentTime(int currentTime) {
  QSequentialAnimationGroup::updateCurrentTime(currentTime);

  auto rootDuration =
      static_cast<QParallelAnimationGroup *>(parent())->duration();

  // Hide layerItem only if the layer is finished and it isn't at the end
  if (currentTime == duration() && currentTime != rootDuration)
    m_layerItem.hide();
  else if (currentTime < duration()) {
    m_layerItem.show();
  }
}

}  // namespace SchMatrix
