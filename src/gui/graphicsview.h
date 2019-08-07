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

 private:
  Tools currentTool = Tools::SelectionTool;
  AnimationModel *animModel = nullptr;
  SchMatrix::GraphicsWidget *currentItem = nullptr;
};

}  // namespace SchMatrix

#endif  // GRAPHICSVIEW_H
