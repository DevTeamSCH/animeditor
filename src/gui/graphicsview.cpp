#include "graphicsview.h"

#include "animationmodel.h"
#include "keyframe.h"
#include "layer.h"
#include "symbol.h"

namespace SchMatrix {

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent) {}

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent) {
  setDragMode(RubberBandDrag);
}

void GraphicsView::setModel(AnimationModel *model) {
  if (m_animationModel == model) return;

  if (model) {
    m_animationModel = model;
  }
}

void GraphicsView::updateCurrentTool(QAction *action) {
  auto name = action->objectName();

  if (name == "actionSelection_Tool") {
    setDragMode(RubberBandDrag);
    m_currentTool = Tools::SelectionTool;
  }
  if (name == "actionFree_Transform_Tool") m_currentTool = Tools::TransformTool;
  if (name == "actionText_Tool") {
    m_currentTool = Tools::TextTool;
    m_currentItemType = ItemTypes::Text;
  }
  if (name == "actionLine_Tool") {
    m_currentItemType = ItemTypes::Line;
    m_currentTool = Tools::LineTool;
  }
  if (name == "actionRectangle_Tool") {
    m_currentItemType = ItemTypes::Rectangle;
    m_currentTool = Tools::RectangleTool;
  }
  if (name == "actionOval_Tool") {
    m_currentItemType = ItemTypes::Oval;
    m_currentTool = Tools::OvalTool;
  }
  if (name == "actionPencil_Tool") {
    m_currentItemType = ItemTypes::Pencil;
    m_currentTool = Tools::PencilTool;
  }
  if (name == "actionPaint_Bucket_Tool") m_currentTool = Tools::PaintBucketTool;
  if (name == "actionHand_Tool") {
    setDragMode(ScrollHandDrag);
    m_currentTool = Tools::HandTool;
  }
  if (name == "actionZoom_Tool") m_currentTool = Tools::ZoomTool;

  // Reset Drag
  if (m_currentTool != Tools::SelectionTool && m_currentTool != Tools::HandTool)
    setDragMode(NoDrag);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event) {
  QGraphicsView::mouseMoveEvent(event);

  if (m_currentTool == Tools::SelectionTool ||
      m_currentTool == Tools::TransformTool ||
      m_currentTool == Tools::ZoomTool || m_currentTool == Tools::HandTool)
    return;

  auto pos = mapToScene(event->pos());
  auto layer = m_animationModel->currentLayer();

  // Creation
  if (!m_currentItem) {
    m_currentItem =
        GraphicsWidget::Create(m_currentItemType, pos.x(), pos.y(), 0, 0);

    layer->addItem(m_currentItem);

    m_animationModel->setData(
        m_animationModel->index(
            m_animationModel->currentLayerIdx(),
            layer->animFramePosition(layer->currentKeyframe())),
        SchMatrix::Key, Qt::UserRole);
  }

  // Editing until released
  auto itemPos = m_currentItem->pos();

  if (pos.y() < itemPos.y()) {    // Top
    if (pos.x() < itemPos.x()) {  // top left
      m_currentItem->setRotation(-180);
      m_currentItem->resize(qAbs(pos.x() - itemPos.x()),
                            qAbs(pos.y() - itemPos.y()));
    } else {  // top right
      m_currentItem->setRotation(-90);
      m_currentItem->resize(qAbs(pos.y() - itemPos.y()),
                            qAbs(pos.x() - itemPos.x()));
    }
  }

  if (pos.y() > itemPos.y()) {    // Bottom
    if (pos.x() < itemPos.x()) {  // bottom left
      m_currentItem->setRotation(90);
      m_currentItem->resize(qAbs(pos.y() - itemPos.y()),
                            qAbs(pos.x() - itemPos.x()));
    } else {  // bottom right
      m_currentItem->setRotation(0);
      m_currentItem->resize(qAbs(pos.x() - itemPos.x()),
                            qAbs(pos.y() - itemPos.y()));
    }
  }
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event) {
  QGraphicsView::mouseReleaseEvent(event);

  // Editing finished
  m_currentItem = nullptr;
}

}  // namespace SchMatrix
