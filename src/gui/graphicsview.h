#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QAction>
#include <QGraphicsView>
#include "graphicswidget.h"

namespace SchMatrix {

class AnimationModel;

enum Tools {
  SelectionTool,
  TransformTool,
  TextTool,
  LineTool,
  RectangleTool,
  OvalTool,
  PencilTool,
  PaintBucketTool,
  HandTool,
  ZoomTool
};

class GraphicsView : public QGraphicsView {
  Q_OBJECT

 public:
  explicit GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);
  explicit GraphicsView(QWidget *parent = nullptr);
  void setModel(SchMatrix::AnimationModel *model);

 public slots:
  void updateCurrentTool(QAction *action);

  // QWidget interface
 protected:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

  // QGraphicsView interface
  void drawBackground(QPainter *painter, const QRectF &rect) override;

 private:
  Tools m_currentTool = Tools::SelectionTool;
  SchMatrix::ItemTypes m_currentItemType = ItemTypes::Rectangle;
  AnimationModel *m_animationModel = nullptr;
  SchMatrix::GraphicsWidget *m_currentItem = nullptr;
  enum Plane { TopLeft, TopRight, BottomLeft, BottomRight };
  Plane m_currentPlane = Plane::BottomRight;
  bool m_creationEnabled = false;
};

}  // namespace SchMatrix

#endif  // GRAPHICSVIEW_H
