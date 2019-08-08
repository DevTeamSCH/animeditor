#ifndef SYMBOL_H
#define SYMBOL_H

#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QList>
#include "animationmodel.h"
#include "core_global.h"

namespace SchMatrix {

class CORESHARED_EXPORT Symbol : public QGraphicsWidget {
  Q_OBJECT

 public:
  explicit Symbol(QList<QGraphicsWidget*> items, QGraphicsScene*,
                  QGraphicsItem* parent = nullptr);
  explicit Symbol(QGraphicsWidget* item, QGraphicsScene*,
                  QGraphicsItem* parent = nullptr);

  void addItem(QGraphicsWidget* item);
  void removeItem(QGraphicsWidget* item);
  void configureLayerItem(QGraphicsItemGroup* layerItem = nullptr);

  AnimationModel* animationModel();

 private:
  AnimationModel m_animationModel;
};

}  // namespace SchMatrix

#endif  // SYMBOL_H
