#ifndef KEYFRAME_H
#define KEYFRAME_H

#include <QParallelAnimationGroup>

namespace SchMatrix {

class Keyframe : public QParallelAnimationGroup {
  Q_OBJECT

 public:
  explicit Keyframe(QObject *parent = nullptr);
};

}  // namespace SchMatrix

#endif  // KEYFRAME_H
