#include "graphicsview.h"

#include "animationmodel.h"

namespace SchMatrix {

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent) {}

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent) {}

void GraphicsView::setModel(AnimationModel *model) {
  if (animModel == model) return;

  if (model) {
    animModel = model;
  }
}

void GraphicsView::updateCurrentTool(QAction *action) {
  auto name = action->objectName();

  if (name == "actionSelection_Tool") currentTool = Tools::SelectionTool;
  if (name == "actionFree_Transform_Tool") currentTool = Tools::TransformTool;
  if (name == "actionText_Tool") currentTool = Tools::TextTool;
  if (name == "actionLine_Tool") currentTool = Tools::LineTool;
  if (name == "actionRectangle_Tool") currentTool = Tools::RectangleTool;
  if (name == "actionOval_Tool") currentTool = Tools::OvalTool;
  if (name == "actionPencil_Tool") currentTool = Tools::PencilTool;
  if (name == "actionPaint_Bucket_Tool") currentTool = Tools::PaintBucketTool;
  if (name == "actionHand_Tool") currentTool = Tools::HandTool;
  if (name == "actionZoom_Tool") currentTool = Tools::ZoomTool;
}

}  // namespace SchMatrix
