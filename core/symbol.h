#ifndef SYMBOL_H
#define SYMBOL_H

#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QList>
#include "animationmodel.h"

namespace SchMatrix {

class Symbol : public QGraphicsWidget {
  Q_OBJECT

 public:
  explicit Symbol(QList<QGraphicsWidget*> items, QGraphicsScene*,
                  QGraphicsItem* parent = nullptr);
  explicit Symbol(QGraphicsWidget* item, QGraphicsScene*,
                  QGraphicsItem* parent = nullptr);
  ~Symbol();

  void addItem(QGraphicsWidget* item);
  void removeItem(QGraphicsWidget* item);

  QList<QGraphicsWidget*> items();
  AnimationModel* getAnimationModel();

 private:
  AnimationModel animModel;
  QGraphicsItemGroup itemGroup;
};

}  // namespace SchMatrix

#endif  // SYMBOL_H
