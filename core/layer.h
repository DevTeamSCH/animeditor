#ifndef LAYER_H
#define LAYER_H

#include <QHash>
#include <QPauseAnimation>
#include <QSequentialAnimationGroup>
#include <QString>
#include "core_global.h"
#include "keyframe.h"

namespace SchMatrix {

class CORESHARED_EXPORT Layer : public QSequentialAnimationGroup {
  Q_OBJECT

 public:
  explicit Layer(QObject *parent = nullptr, QString name = "layer",
                 int zOrder = 0);
  QList<Keyframe *> keyframes();
  Keyframe *currentKeyframe();
  Keyframe *nextKeyframe();
  Keyframe *prevKeyframe();

  QString getName();
  int getZOrder();
  void setName(const QString &name);
  void setZOrder(const int &zOrder);

 private:
  QString name;
  int zOrder;
};

}  // namespace SchMatrix

#endif  // LAYER_H
