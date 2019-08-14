#include "keyframe.h"

#include <QGraphicsScene>
#include <QPauseAnimation>
#include "config.h"
#include "graphicswidget.h"
#include "symbol.h"

namespace SchMatrix {

// Parent is always Layer
Keyframe::Keyframe(QObject *parent) : QParallelAnimationGroup(parent) {
  // Add 1 frame long pause
  // 1 Keyframe is always 1 frame long
  addAnimation(new QPauseAnimation(SchMatrix::frameLength, this));
}

// Set parent after construction
Keyframe::Keyframe(const Keyframe &other) : Keyframe(nullptr) {
  auto &animAssign = other.m_animationAssignments;

  for (auto object : animAssign.keys()) {
    // Clone object
    auto newObject = object->clone();

    // TODO Add Symbol's root animation

    // Copy properties
    for (auto &name : animAssign[object].keys()) {
      assignProperty(newObject, name, animAssign[object][name]->startValue());
    }
  }
}

Keyframe::~Keyframe() {
  // Keyframe is the only class which is allowed to delete items when destroyed
  for (auto item : m_animationAssignments.keys()) {
    deleteObject(item);
  }
}

void Keyframe::assignProperty(SchMatrix::GraphicsWidget *object,
                              const QByteArray &name, const QVariant &value,
                              bool start) {
  if (!object) {
    qWarning(
        "Keyframe::assignProperty: cannot assign property '%s' of null object",
        name.data());
    return;
  }

  if (m_animationAssignments[object].contains(name)) {
    auto objectAnim = m_animationAssignments[object][name];
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
  m_animationAssignments[object][name] = objectAnim;
  addAnimation(objectAnim);
}

QPropertyAnimation *Keyframe::propertyAnimation(
    SchMatrix::GraphicsWidget *object, const QByteArray &name) const {
  return m_animationAssignments[object][name];
}

void Keyframe::addObject(SchMatrix::GraphicsWidget *object) {
  if (m_animationAssignments.contains(object)) return;

  // Store important properties
  // pos is in parent coordinates
  assignProperty(object, "pos", object->pos());
  assignProperty(object, "rotation", object->rotation());
  assignProperty(object, "scale", object->scale());
}

// Only remove object from assingnments and delete it's animations
void Keyframe::removeObject(SchMatrix::GraphicsWidget *object) {
  if (!m_animationAssignments.contains(object)) return;

  for (auto anim : m_animationAssignments[object]) {
    removeAnimation(anim);
    delete anim;
  }

  m_animationAssignments.remove(object);
}

// Remove + delete
void Keyframe::deleteObject(SchMatrix::GraphicsWidget *object) {
  removeObject(object);

  // https://doc.qt.io/qt-5/qgraphicsitem.html#dtor.QGraphicsItem
  auto scene = object->scene();
  if (scene) scene->removeItem(object);

  delete object;
}

QList<SchMatrix::GraphicsWidget *> Keyframe::objects() const {
  return m_animationAssignments.keys();
}

bool Keyframe::empty() const { return m_animationAssignments.empty(); }

// Between 2 keyframes you can only interpolate/tween only one symbol and no
// other items
bool Keyframe::canInterpolate() const {
  if (m_animationAssignments.size() != 1 ||
      !qobject_cast<SchMatrix::Symbol *>(*m_animationAssignments.keyBegin()))
    return false;

  return true;
}

void Keyframe::interpolate(int duration, const Keyframe *nextKeyframe) {
  auto currentObject = *m_animationAssignments.keyBegin();
  auto otherObject = *nextKeyframe->m_animationAssignments.keyBegin();

  // Only intrepolate the most important properties for now
  m_animationAssignments[currentObject]["pos"]->setDuration(duration);
  m_animationAssignments[currentObject]["rotation"]->setDuration(duration);
  m_animationAssignments[currentObject]["scale"]->setDuration(duration);

  assignProperty(
      currentObject, "pos",
      nextKeyframe->m_animationAssignments[otherObject]["pos"]->startValue(),
      false);
  assignProperty(currentObject, "rotation",
                 nextKeyframe->m_animationAssignments[otherObject]["rotation"]
                     ->startValue(),
                 false);
  assignProperty(
      currentObject, "scale",
      nextKeyframe->m_animationAssignments[otherObject]["scale"]->startValue(),
      false);
}

}  // namespace SchMatrix
