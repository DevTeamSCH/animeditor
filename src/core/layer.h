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
class GraphicsWidget;

class CORESHARED_EXPORT Layer : public QSequentialAnimationGroup {
  Q_OBJECT

 public:
  explicit Layer(QGraphicsScene *scene, QObject *parent = nullptr,
                 const QString &name = "layer", int zValue = 0);
  explicit Layer(QObject *parent = nullptr);
  explicit Layer(const Layer &other);

  QList<QAbstractAnimation *> animations() const;
  QList<QPauseAnimation *> pauses() const;
  QList<Keyframe *> keyframes() const;
  Keyframe *currentKeyframe() const;
  Keyframe *nextKeyframe() const;
  Keyframe *prevKeyframe() const;
  int animFramePosition(QAbstractAnimation *anim) const;
  QPauseAnimation *currentPause() const;

  int zValue() const;
  void setZValue(const int &m_zValue);

  QAbstractAnimation *animationAtMsec(int msec) const;

  void addItem(SchMatrix::GraphicsWidget *item);
  void removeItem(SchMatrix::GraphicsWidget *item);
  SchMatrix::Symbol *convertToSymbol(
      const QList<SchMatrix::GraphicsWidget *> &items);
  void deleteItem(SchMatrix::GraphicsWidget *item);
  void deleteKeyframe(SchMatrix::Keyframe *keyframe);

 private slots:
  void updateLayer(QAbstractAnimation *current);

 private:
  int m_zValue;
  QList<QGraphicsWidget *> m_currentItems;
  QGraphicsScene *m_scene = nullptr;
  SchMatrix::Keyframe *m_lastKeyframe = nullptr;

  // QAbstractAnimation interface
 protected:
  void updateCurrentTime(int currentTime) override;
};

}  // namespace SchMatrix

#endif  // LAYER_H
