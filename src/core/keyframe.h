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
class GraphicsWidget;

class CORESHARED_EXPORT Keyframe : public QParallelAnimationGroup {
  Q_OBJECT

 public:
  explicit Keyframe(QObject *parent = nullptr);
  Keyframe(const Keyframe &other);
  ~Keyframe() override;

  void assignProperty(SchMatrix::GraphicsWidget *object, const QByteArray &name,
                      const QVariant &value, bool start = true);
  QPropertyAnimation *propertyAnimation(SchMatrix::GraphicsWidget *object,
                                        const QByteArray &name);

  void addObject(SchMatrix::GraphicsWidget *object);
  void removeObject(SchMatrix::GraphicsWidget *object);
  void deleteObject(SchMatrix::GraphicsWidget *object);

  QList<SchMatrix::GraphicsWidget *> objects();
  bool empty();
  bool canInterpolate();
  void interpolate(int duration, const Keyframe *nextKeyframe);

 private:
  QHash<SchMatrix::GraphicsWidget *, QHash<QByteArray, QPropertyAnimation *>>
      m_animationAssignments;
};

}  // namespace SchMatrix

#endif  // KEYFRAME_H
