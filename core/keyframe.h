#ifndef KEYFRAME_H
#define KEYFRAME_H

#include <QByteArray>
#include <QGraphicsWidget>
#include <QHash>
#include <QList>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSharedPointer>
#include "core_global.h"

namespace SchMatrix {

class CORESHARED_EXPORT Keyframe : public QParallelAnimationGroup {
  Q_OBJECT

 public:
  explicit Keyframe(QObject *parent = nullptr);
  Keyframe(const Keyframe &other);
  void assignProperty(QGraphicsWidget *object, const QByteArray &name,
                      const QVariant &value, bool start = true);
  QPropertyAnimation *getAnimation(QGraphicsWidget *object,
                                   const QByteArray &name);
  void removeObject(QGraphicsWidget *object);
  QList<QGraphicsWidget *> objects();

 private:
  QHash<QSharedPointer<QGraphicsWidget>,
        QHash<QByteArray, QPropertyAnimation *>>
      animationAssignments;
};

}  // namespace SchMatrix

#endif  // KEYFRAME_H