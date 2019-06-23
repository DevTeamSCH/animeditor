#ifndef LAYER_H
#define LAYER_H

#include <QHash>
#include <QPauseAnimation>
#include <QSequentialAnimationGroup>
#include "keyframe.h"

namespace SchMatrix {

class Layer : public QSequentialAnimationGroup {
  Q_OBJECT
 public:
  explicit Layer(QObject *parent = nullptr);
  QList<Keyframe *> keyframes();
  Keyframe *currentKeyframe();
  Keyframe *nextKeyframe();
  Keyframe *prevKeyframe();
};

}  // namespace SchMatrix

#endif  // LAYER_H
