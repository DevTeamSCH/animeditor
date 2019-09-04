#include "rootanimation.h"

#include "layer.h"

namespace SchMatrix {

RootAnimation::RootAnimation(QObject *parent)
    : QParallelAnimationGroup(parent) {}

RootAnimation::RootAnimation(const RootAnimation &other) {
  for (int i = 0; i < other.animationCount(); ++i) {
    // Clone layer
    auto newLayer = new SchMatrix::Layer(
        *static_cast<SchMatrix::Layer *>(other.animationAt(i)));

    addAnimation(newLayer);
  }
}

RootAnimation &RootAnimation::operator=(const RootAnimation &other) {
  for (int i = 0; i < other.animationCount(); ++i) {
    // Clone layer
    auto newLayer = new SchMatrix::Layer(
        *static_cast<SchMatrix::Layer *>(other.animationAt(i)));

    addAnimation(newLayer);
  }

  return *this;
}

}  // namespace SchMatrix
