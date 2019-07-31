#include "layer.h"

#include <QGraphicsScene>
#include <QList>
#include "config.h"

namespace SchMatrix {

Layer::Layer(QGraphicsScene *scene, QObject *parent, QString name, int zOrder)
    : QSequentialAnimationGroup(parent), name(name), zOrder(zOrder) {
  scene->addItem(&layerItem);
  layerItem.setZValue(zOrder);

  connect(this, &QSequentialAnimationGroup::currentAnimationChanged, this,
          &Layer::updateLayer);
}

Layer::~Layer() {
  for (auto i : layerItem.childItems()) {
    layerItem.removeFromGroup(i);
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
    auto anim = animationAt(i);
    if (qobject_cast<QPauseAnimation *>(anim))
      pauseAnims.append(static_cast<QPauseAnimation *>(anim));
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
  auto anim = currentAnimation();

  if (qobject_cast<Keyframe *>(anim))
    return static_cast<Keyframe *>(anim);
  else if (animationCount() > 1)
    return static_cast<Keyframe *>(animationAt(indexOfAnimation(anim) - 1));

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

  if (!currentAnim) {  // anim is pause
    return keyframe;
  } else if (idx != 0) {  // anim is (blank)keyframe
    return keys[idx - 1];
  }

  return nullptr;
}

int Layer::animFramePosition(QAbstractAnimation *anim) {
  auto animIdx = indexOfAnimation(anim);
  int frames = 0;

  for (int i = 0; i < animIdx; ++i) {
    frames += animationAt(i)->duration() / SchMatrix::frameLength;
  }

  return frames;
}

QString Layer::getName() const { return name; }

int Layer::getZOrder() const { return zOrder; };

void Layer::setName(const QString &newName) { name = newName; }

void Layer::setZOrder(const int &order) {
  zOrder = order;
  layerItem.setZValue(zOrder);
}

void Layer::deleteEmptyPauses() {
  for (auto p : pauses()) {
    if (p->duration() == 0) delete p;
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

void Layer::addItem(QGraphicsWidget *item) {
  layerItem.addToGroup(item);
  currentKeyframe()->addObject(item);
}

void Layer::removeItem(QGraphicsWidget *item) {
  layerItem.removeFromGroup(item);
  currentKeyframe()->removeObject(item);
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
  if (keyframe == lastKeyframe || !keyframe) return;

  lastKeyframe = keyframe;

  // remove previous objects
  for (auto item : layerItem.childItems()) {
    layerItem.removeFromGroup(item);
    layerItem.scene()->removeItem(item);
  }

  // skip blank keyframe
  if (keyframe->animationCount() == 1) return;

  // add current objects
  for (auto item : keyframe->objects()) {
    layerItem.addToGroup(item);
  }

  layerItem.scene()->update();
}

void Layer::updateCurrentTime(int currentTime) {
  QSequentialAnimationGroup::updateCurrentTime(currentTime);

  auto rootDuration =
      static_cast<QParallelAnimationGroup *>(parent())->duration();

  // Hide layerItem only if the layer is finished and it isn't at the end
  if (currentTime == duration() && currentTime != rootDuration)
    layerItem.hide();
  else if (currentTime < duration()) {
    layerItem.show();
  }
}

}  // namespace SchMatrix
