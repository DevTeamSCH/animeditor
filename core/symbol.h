#ifndef SYMBOL_H
#define SYMBOL_H

#include <QGraphicsWidget>

namespace SchMatrix {

class Symbol : public QGraphicsWidget {
  Q_OBJECT

 public:
  explicit Symbol(QGraphicsItem *parent = nullptr);
};

}  // namespace SchMatrix

#endif  // SYMBOL_H
