#ifndef LAYER_H
#define LAYER_H

#include <QGraphicsItemGroup>
#include <QHash>
#include <QPauseAnimation>
#include <QSequentialAnimationGroup>
#include <QString>
#include "core_global.h"

namespace SchMatrix {

class Keyframe;
class Symbol;

class CORESHARED_EXPORT Layer : public QSequentialAnimationGroup {
  Q_OBJECT

 public:
  explicit Layer(QGraphicsScene *scene, QObject *parent = nullptr,
                 QString name = "layer", int zOrder = 0);
  ~Layer() override;

  QList<QAbstractAnimation *> animations() const;
  QList<QPauseAnimation *> pauses() const;
  QList<Keyframe *> keyframes() const;
  Keyframe *currentKeyframe() const;
  Keyframe *nextKeyframe() const;
  Keyframe *prevKeyframe() const;
  int animFramePosition(QAbstractAnimation *anim);

  QString getName() const;
  int getZOrder() const;
  void setName(const QString &name);
  void setZOrder(const int &zOrder);

  QAbstractAnimation *animationAtMsec(int msec) const;

  void addItem(QGraphicsWidget *item);
  void removeItem(QGraphicsWidget *item);
  void setGroupParent(SchMatrix::Symbol *symbol);

 private slots:
  void updateLayer(QAbstractAnimation *current);

 private:
  QString name;
  int zOrder;
  QGraphicsItemGroup layerItem;
  Keyframe *lastKeyframe;

  // QAbstractAnimation interface
 protected:
  void updateCurrentTime(int currentTime) override;
};

}  // namespace SchMatrix

#endif  // LAYER_H
