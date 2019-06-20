#ifndef KEYFRAME_H
#define KEYFRAME_H

#include <QGraphicsObject>
#include <QHash>
#include <QParallelAnimationGroup>

namespace SchMatrix {

class Keyframe : public QParallelAnimationGroup {
  Q_OBJECT

 public:
  explicit Keyframe(QObject *parent = nullptr);
  void assignProperty(QGraphicsObject *object, const char *name,
                      const QVariant &value);

 private:
  QHash<QGraphicsObject *, QHash<QString, QVariant>> propertyAssignments;
};

}  // namespace SchMatrix

#endif  // KEYFRAME_H
