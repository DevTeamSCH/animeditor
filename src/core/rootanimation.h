#ifndef ROOTANIMATION_H
#define ROOTANIMATION_H

#include <QParallelAnimationGroup>
#include "core_global.h"

namespace SchMatrix {

class CORESHARED_EXPORT RootAnimation : public QParallelAnimationGroup {
  Q_OBJECT

 public:
  explicit RootAnimation(QObject *parent = nullptr);
};

}  // namespace SchMatrix

#endif  // ROOTANIMATION_H
