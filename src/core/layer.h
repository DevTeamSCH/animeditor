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
                 const QString &name = "layer", int zValue = 0);
  ~Layer() override;

  QList<QAbstractAnimation *> animations() const;
  QList<QPauseAnimation *> pauses() const;
  QList<Keyframe *> keyframes() const;
  Keyframe *currentKeyframe() const;
  Keyframe *nextKeyframe() const;
  Keyframe *prevKeyframe() const;
  int animFramePosition(QAbstractAnimation *anim);

  int zValue() const;
  void setZValue(const int &m_zValue);

  QAbstractAnimation *animationAtMsec(int msec) const;

  void addItem(QGraphicsWidget *item);
  void removeItem(QGraphicsWidget *item);
  void setGroupParent(SchMatrix::Symbol *symbol);

 private slots:
  void updateLayer(QAbstractAnimation *current);

 private:
  int m_zValue;
  QGraphicsItemGroup m_layerItem;
  SchMatrix::Keyframe *m_lastKeyframe;

  // QAbstractAnimation interface
 protected:
  void updateCurrentTime(int currentTime) override;
};

}  // namespace SchMatrix

#endif  // LAYER_H
