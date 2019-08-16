#include "graphicsview.h"

#include "animationmodel.h"

namespace SchMatrix {

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent) {}

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent) {}

void GraphicsView::setModel(AnimationModel *model) {
  if (m_animationModel == model) return;

  if (model) {
    m_animationModel = model;
  }
}

void GraphicsView::updateCurrentTool(QAction *action) {
  auto name = action->objectName();

  if (name == "actionSelection_Tool") m_currentTool = Tools::SelectionTool;
  if (name == "actionFree_Transform_Tool") m_currentTool = Tools::TransformTool;
  if (name == "actionText_Tool") m_currentTool = Tools::TextTool;
  if (name == "actionLine_Tool") m_currentTool = Tools::LineTool;
  if (name == "actionRectangle_Tool") m_currentTool = Tools::RectangleTool;
  if (name == "actionOval_Tool") m_currentTool = Tools::OvalTool;
  if (name == "actionPencil_Tool") m_currentTool = Tools::PencilTool;
  if (name == "actionPaint_Bucket_Tool") m_currentTool = Tools::PaintBucketTool;
  if (name == "actionHand_Tool") m_currentTool = Tools::HandTool;
  if (name == "actionZoom_Tool") m_currentTool = Tools::ZoomTool;
}

}  // namespace SchMatrix
