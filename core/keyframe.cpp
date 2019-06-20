#include "keyframe.h"

namespace SchMatrix {

Keyframe::Keyframe(QObject *parent) : QParallelAnimationGroup(parent) {}

void Keyframe::assignProperty(QGraphicsObject *object, const char *name,
                              const QVariant &value) {
  if (!object) {
    qWarning(
        "Keyframe::assignProperty: cannot assign property '%s' of null object",
        name);
    return;
  }

  if (propertyAssignments.contains(object)) {
    propertyAssignments[object][name] = value;
    return;
  }

  propertyAssignments[object] = QHash<QString, QVariant>{{name, value}};
}

}  // namespace SchMatrix
