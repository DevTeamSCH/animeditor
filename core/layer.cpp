#include "layer.h"

#include <QList>

namespace SchMatrix {

Layer::Layer(QObject *parent, QString name, int zOrder)
    : QSequentialAnimationGroup(parent), name(name), zOrder(zOrder) {}

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
  else
    return static_cast<Keyframe *>(animationAt(indexOfAnimation(anim) - 1));
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
  auto idx = keys.indexOf(currentKeyframe());

  if (idx == 0) return nullptr;

  return keys[idx - 1];
}

QString Layer::getName() const { return name; }

int Layer::getZOrder() const { return zOrder; };

void Layer::setName(const QString &newName) { name = newName; }

void Layer::setZOrder(const int &order) { zOrder = order; }

void Layer::deleteEmptyPauses() {
  for (auto p : pauses()) {
    if (p->duration() == 0) delete p;
  }
}

QAbstractAnimation *Layer::animationAtMsec(int msec) const {
  auto root = static_cast<QAbstractAnimation *>(parent());

  root->setCurrentTime(msec);

  return currentAnimation();
};

}  // namespace SchMatrix
