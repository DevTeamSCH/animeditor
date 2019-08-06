#include "keyframe.h"

#include <QGraphicsScene>
#include <QPauseAnimation>
#include "config.h"
#include "symbol.h"

namespace SchMatrix {

// Parent is always Layer
Keyframe::Keyframe(QObject *parent) : QParallelAnimationGroup(parent) {
  // Add 1 frame long pause
  // 1 Keyframe is always 1 frame long
  addAnimation(new QPauseAnimation(SchMatrix::frameLength, this));
}

Keyframe::Keyframe(const Keyframe &other) : Keyframe(other.parent()) {
  // set the Layer animation as parent
  setParent(other.parent());

  // TODO clone object
}

Keyframe::~Keyframe() {
  // Keyframe is the only class which is allowed to delete items when destroyed
  for (auto item : animationAssignments.keys()) {
    deleteObject(item);
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

// Only remove object from assingnments and delete it's animations
void Keyframe::removeObject(QGraphicsWidget *object) {
  if (!animationAssignments.contains(object)) return;

  for (auto anim : animationAssignments[object]) {
    removeAnimation(anim);
    delete anim;
  }

  animationAssignments.remove(object);
}

// Remove + delete
void Keyframe::deleteObject(QGraphicsWidget *object) {
  removeObject(object);

  // https://doc.qt.io/qt-5/qgraphicsitem.html#dtor.QGraphicsItem
  auto scene = object->scene();
  if (scene) scene->removeItem(object);

  delete object;
}

QList<QGraphicsWidget *> Keyframe::objects() {
  return animationAssignments.keys();
}

bool Keyframe::empty() { return animationAssignments.empty(); }

}  // namespace SchMatrix
