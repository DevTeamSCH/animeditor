#ifndef SYMBOL_H
#define SYMBOL_H

#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QList>
#include "animationmodel.h"
#include "core_global.h"
#include "graphicswidget.h"

namespace SchMatrix {

class CORESHARED_EXPORT Symbol : public SchMatrix::GraphicsWidget {
  Q_OBJECT

 public:
  explicit Symbol(QGraphicsScene*, QGraphicsItem* parent = nullptr);
  explicit Symbol(const Symbol& other);

  void addItem(SchMatrix::GraphicsWidget* item);
  void removeItem(SchMatrix::GraphicsWidget* item);

  AnimationModel* animationModel();

  enum { Type = SchMatrix::ItemTypes::SymbolItem };

  // QGraphicsItem interface
  int type() const override;

  // GraphicsWidget interface
  GraphicsWidget* clone() const override;

 private:
  AnimationModel m_animationModel;
};

}  // namespace SchMatrix

#endif  // SYMBOL_H
