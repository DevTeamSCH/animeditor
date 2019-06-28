#include "keyframe.h"

namespace SchMatrix {

Keyframe::Keyframe(QObject *parent) : QParallelAnimationGroup(parent) {}

Keyframe::Keyframe(const Keyframe &other) {
  auto &animAssign = other.animationAssignments;

  // set the root animation as parent
  setParent(other.parent());

  for (auto &obj : animAssign.keys()) {
    for (auto &name : animAssign[obj].keys()) {
      assignProperty(obj.get(), name, animAssign[obj][name]->startValue());
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

  QSharedPointer<QGraphicsWidget> objectPtr(object);

  if (animationAssignments[objectPtr].contains(name)) {
    auto objectAnim = animationAssignments[objectPtr][name];
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
  animationAssignments[objectPtr][name] = objectAnim;
  addAnimation(objectAnim);
}

QPropertyAnimation *Keyframe::getAnimation(QGraphicsWidget *object,
                                           const QByteArray &name) {
  QSharedPointer<QGraphicsWidget> objectPtr(object);
  return animationAssignments[objectPtr][name];
}

void Keyframe::removeObject(QGraphicsWidget *object) {
  QSharedPointer<QGraphicsWidget> objectPtr(object);

  for (auto anim : animationAssignments[objectPtr]) {
    removeAnimation(anim);
    delete anim;
  }

  animationAssignments.remove(objectPtr);
}

QList<QGraphicsWidget *> Keyframe::objects() {
  QList<QGraphicsWidget *> list;

  for (auto objectPtr : animationAssignments.keys()) {
    list.append(objectPtr.get());
  }

  return list;
}

}  // namespace SchMatrix
