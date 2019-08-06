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

class Symbol;

class CORESHARED_EXPORT Keyframe : public QParallelAnimationGroup {
  Q_OBJECT

 public:
  explicit Keyframe(QObject *parent = nullptr);
  Keyframe(const Keyframe &other);
  ~Keyframe() override;

  void assignProperty(QGraphicsWidget *object, const QByteArray &name,
                      const QVariant &value, bool start = true);
  QPropertyAnimation *propertyAnimation(QGraphicsWidget *object,
                                        const QByteArray &name);

  void addObject(QGraphicsWidget *object);
  void removeObject(QGraphicsWidget *object);
  void deleteObject(QGraphicsWidget *object);

  QList<QGraphicsWidget *> objects();
  bool empty();

 private:
  QHash<QGraphicsWidget *, QHash<QByteArray, QPropertyAnimation *>>
      m_animationAssignments;
};

}  // namespace SchMatrix

#endif  // KEYFRAME_H
