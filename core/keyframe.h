#ifndef KEYFRAME_H
#define KEYFRAME_H

#include <QGraphicsWidget>
#include <QHash>
#include <QParallelAnimationGroup>
#include <QSharedPointer>

namespace SchMatrix {

class Keyframe : public QParallelAnimationGroup {
  Q_OBJECT

 public:
  explicit Keyframe(QObject *parent = nullptr);
  void assignProperty(QGraphicsWidget *object, const char *name,
                      const QVariant &value);

 private:
  QHash<QSharedPointer<QGraphicsWidget>, QHash<QString, QVariant>>
      propertyAssignments;
};

}  // namespace SchMatrix

#endif  // KEYFRAME_H
