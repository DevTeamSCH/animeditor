#include "keyframe.h"

namespace SchMatrix {

Keyframe::Keyframe(QObject *parent) : QParallelAnimationGroup(parent) {}

void Keyframe::assignProperty(QGraphicsWidget *object, const char *name,
                              const QVariant &value) {
  if (!object) {
    qWarning(
        "Keyframe::assignProperty: cannot assign property '%s' of null object",
        name);
    return;
  }

  QSharedPointer<QGraphicsWidget> objectPtr(object);

  if (propertyAssignments.contains(objectPtr)) {
    propertyAssignments[objectPtr][name] = value;
    return;
  }

  propertyAssignments[objectPtr] = QHash<QString, QVariant>{{name, value}};
}

}  // namespace SchMatrix
