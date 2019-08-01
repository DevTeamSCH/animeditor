#include "keyframe.h"

#include <QPauseAnimation>
#include "config.h"
#include "symbol.h"

namespace SchMatrix {

Keyframe::Keyframe(QObject *parent) : QParallelAnimationGroup(parent) {
  // Add 1 frame long pause
  // 1 Keyframe is always 1 frame long
  addAnimation(new QPauseAnimation(SchMatrix::frameLength, this));
}

Keyframe::Keyframe(const Keyframe &other) : Keyframe(other.parent()) {
  auto &animAssign = other.animationAssignments;

  // set the root animation as parent
  setParent(other.parent());

  for (auto obj : animAssign.keys()) {
    for (auto &name : animAssign[obj].keys()) {
      assignProperty(obj, name, animAssign[obj][name]->startValue());
    }
  }
}

void Keyframe::assignProperty(QGraphicsWidget *object, const QByteArray &name,
                              const QVariant &value, bool start) {
  if (!object) {
    qWarning(
        "Keyframe::assignProperty: cannot assign property '%s' of null object",
        name.data());
    return;
  }

  if (animationAssignments[object].contains(name)) {
    auto objectAnim = animationAssignments[object][name];
    if (objectAnim->duration() == 0) {  // no interpolation
      objectAnim->setStartValue(value);
      objectAnim->setEndValue(value);
    } else {  // with interpolation
      if (start)
        objectAnim->setStartValue(value);
      else
        objectAnim->setEndValue(value);
    }

    return;
  }

  auto objectAnim = new QPropertyAnimation(object, name, this);
  objectAnim->setStartValue(value);
  objectAnim->setEndValue(value);
  objectAnim->setDuration(0);
  animationAssignments[object][name] = objectAnim;
  addAnimation(objectAnim);
}

QPropertyAnimation *Keyframe::getAnimation(QGraphicsWidget *object,
                                           const QByteArray &name) {
  return animationAssignments[object][name];
}

void Keyframe::addObject(QGraphicsWidget *object) {
  if (animationAssignments.contains(object)) return;
}

void Keyframe::removeObject(QGraphicsWidget *object) {
  if (!animationAssignments.contains(object)) return;

  for (auto anim : animationAssignments[object]) {
    removeAnimation(anim);
    delete anim;
  }

  animationAssignments.remove(object);
}

QList<QGraphicsWidget *> Keyframe::objects() {
  QList<QGraphicsWidget *> list;

  for (auto object : animationAssignments.keys()) {
    list.append(object);
  }

  return list;
}

bool Keyframe::empty() { return animationAssignments.empty(); }

}  // namespace SchMatrix
