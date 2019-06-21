#ifndef KEYFRAME_H
#define KEYFRAME_H

#include <QGraphicsWidget>
#include <QHash>
#include <QList>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSharedPointer>

namespace SchMatrix {

class Keyframe : public QParallelAnimationGroup {
  Q_OBJECT

 public:
  explicit Keyframe(QObject *parent = nullptr);
  void assignProperty(QGraphicsWidget *object, const char *name,
                      const QVariant &value, bool start = true);
  QPropertyAnimation *getAnimation(QGraphicsWidget *object, const char *name);
  void removeObject(QGraphicsWidget *object);
  QList<QGraphicsWidget *> objects();

 private:
  QHash<QSharedPointer<QGraphicsWidget>, QHash<QString, QPropertyAnimation *>>
      animationAssignments;
};

}  // namespace SchMatrix

#endif  // KEYFRAME_H
