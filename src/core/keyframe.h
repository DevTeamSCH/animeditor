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

enum FrameTypes {
  Frame,
  EndOfFrame,
  Key,
  BlankKey,
  PotentialFrame,
  TweenedFrame
};

class Symbol;
class GraphicsWidget;

class CORESHARED_EXPORT Keyframe : public QParallelAnimationGroup {
  Q_OBJECT

 public:
  explicit Keyframe(QObject *parent = nullptr, int startFrame = 0);
  explicit Keyframe(const Keyframe &other);
  ~Keyframe() override;

  void assignProperty(SchMatrix::GraphicsWidget *object, const QByteArray &name,
                      const QVariant &value, bool start = true);
  QPropertyAnimation *propertyAnimation(SchMatrix::GraphicsWidget *object,
                                        const QByteArray &name) const;

  void addObject(SchMatrix::GraphicsWidget *object);
  void removeObject(SchMatrix::GraphicsWidget *object);
  void deleteObject(SchMatrix::GraphicsWidget *object);

  QList<SchMatrix::GraphicsWidget *> objects() const;
  bool empty() const;
  bool canInterpolate() const;
  void interpolate(const Keyframe *nextKeyframe);
  static Keyframe *getKeyframe(SchMatrix::GraphicsWidget *widget);

  int startFrame() const;
  void setStartFrame(int startFrame);
  int endFrame() const;
  int paint(int pos = -1);

  // QAbstractAnimation interface
  int duration() const override;
  void setDuration(int msecs);

 private:
  QHash<SchMatrix::GraphicsWidget *, QHash<QByteArray, QPropertyAnimation *>>
      m_animationAssignments;
  static QHash<SchMatrix::GraphicsWidget *, Keyframe *> m_widgetAssignment;
  int m_duration;
  int m_startFrame;
  int m_endFrame;
  bool m_interpolated = false;
};

}  // namespace SchMatrix

#endif  // KEYFRAME_H
