#ifndef LAYER_H
#define LAYER_H

#include <QHash>
#include <QPauseAnimation>
#include <QSequentialAnimationGroup>
#include <QString>
#include "keyframe.h"

namespace SchMatrix {

class Layer : public QSequentialAnimationGroup {
  Q_OBJECT
 public:
  explicit Layer(QObject *parent = nullptr);
  explicit Layer(QString name = "layer", int zOrder = 0,
                 QObject *parent = nullptr);
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
