#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

namespace SchMatrix {

class GraphicsView : public QGraphicsView {
  Q_OBJECT

 public:
  explicit GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);
  explicit GraphicsView(QWidget *parent = nullptr);
};

}  // namespace SchMatrix

#endif  // GRAPHICSVIEW_H
