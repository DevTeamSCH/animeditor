#include "graphicsview.h"

#include "animationmodel.h"
#include "graphicslinewidget.h"
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

  // Creation disabled
  if (name == "actionSelection_Tool") {
    setDragMode(RubberBandDrag);
    m_currentTool = Tools::SelectionTool;
    m_creationEnabled = false;
  }
  if (name == "actionFree_Transform_Tool") {
    m_currentTool = Tools::TransformTool;
    m_creationEnabled = false;
  }
  if (name == "actionPaint_Bucket_Tool") {
    m_currentTool = Tools::PaintBucketTool;
    m_creationEnabled = false;
  }
  if (name == "actionHand_Tool") {
    setDragMode(ScrollHandDrag);
    m_currentTool = Tools::HandTool;
    m_creationEnabled = false;
  }
  if (name == "actionZoom_Tool") {
    m_currentTool = Tools::ZoomTool;
    m_creationEnabled = false;
  };

  // Creation enabled
  if (name == "actionText_Tool") {
    m_currentTool = Tools::TextTool;
    m_currentItemType = ItemTypes::Text;
    m_creationEnabled = true;
  }
  if (name == "actionLine_Tool") {
    m_currentItemType = ItemTypes::Line;
    m_currentTool = Tools::LineTool;
    m_creationEnabled = true;
  }
  if (name == "actionRectangle_Tool") {
    m_currentItemType = ItemTypes::Rectangle;
    m_currentTool = Tools::RectangleTool;
    m_creationEnabled = true;
  }
  if (name == "actionOval_Tool") {
    m_currentItemType = ItemTypes::Oval;
    m_currentTool = Tools::OvalTool;
    m_creationEnabled = true;
  }
  if (name == "actionPencil_Tool") {
    m_currentItemType = ItemTypes::Pencil;
    m_currentTool = Tools::PencilTool;
    m_creationEnabled = true;
  }

  // Reset Drag
  if (m_currentTool != Tools::SelectionTool && m_currentTool != Tools::HandTool)
    setDragMode(NoDrag);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event) {
  QGraphicsView::mouseMoveEvent(event);

  if (m_creationEnabled == false) return;

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
  QTransform transform;

  if (pos.y() < itemPos.y()) {    // Top
    if (pos.x() < itemPos.x()) {  // top left
      m_currentItem->setTransform(transform.rotate(-180));
      m_currentItem->resize(qAbs(pos.x() - itemPos.x()),
                            qAbs(pos.y() - itemPos.y()));

      m_currentPlane = Plane::TopLeft;
    } else {  // top right
      m_currentItem->setTransform(transform.rotate(-90));
      m_currentItem->resize(qAbs(pos.y() - itemPos.y()),
                            qAbs(pos.x() - itemPos.x()));

      m_currentPlane = Plane::TopRight;
    }
  }

  if (pos.y() > itemPos.y()) {    // Bottom
    if (pos.x() < itemPos.x()) {  // bottom left
      m_currentItem->setTransform(transform.rotate(90));
      m_currentItem->resize(qAbs(pos.y() - itemPos.y()),
                            qAbs(pos.x() - itemPos.x()));

      m_currentPlane = Plane::BottomLeft;
    } else {  // bottom right
      m_currentItem->setTransform(transform.rotate(0));
      m_currentItem->resize(qAbs(pos.x() - itemPos.x()),
                            qAbs(pos.y() - itemPos.y()));

      m_currentPlane = Plane::BottomRight;
    }
  }

  if (m_currentItemType == ItemTypes::Line) {
    auto width = m_currentItem->size().width();
    auto height = m_currentItem->size().height();
    auto line = static_cast<SchMatrix::GraphicsLineWidget *>(m_currentItem);

    line->setLine(0, 0, width, height);
  }
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event) {
  QGraphicsView::mouseReleaseEvent(event);

  if (!m_currentItem) return;

  auto layer = m_animationModel->currentLayer();
  auto width = m_currentItem->size().width();
  auto height = m_currentItem->size().height();

  m_currentItem->resetTransform();

  if (m_currentPlane == Plane::TopLeft) m_currentItem->moveBy(-width, -height);

  if (m_currentPlane == Plane::TopRight) {
    m_currentItem->resize(height, width);
    m_currentItem->moveBy(0, -width);

    if (m_currentItemType == ItemTypes::Line) {
      auto line = static_cast<SchMatrix::GraphicsLineWidget *>(m_currentItem);

      line->setLine(0, width, height, 0);
    }
  }
  if (m_currentPlane == Plane::BottomLeft) {
    if (m_currentItemType == ItemTypes::Line) {
      auto line = static_cast<SchMatrix::GraphicsLineWidget *>(m_currentItem);

      line->setLine(0, width, height, 0);
    }
    m_currentItem->resize(height, width);
    m_currentItem->moveBy(-height, 0);
  }

  auto center = m_currentItem->boundingRect().center();
  m_currentItem->setTransformOriginPoint(center);
  m_currentItem->setUpdateTransformOriginPoint(true);

  // Update rotation, geometry after editing
  layer->currentKeyframe()->assignProperty(m_currentItem, "rotation",
                                           m_currentItem->rotation());
  layer->currentKeyframe()->assignProperty(m_currentItem, "geometry",
                                           m_currentItem->geometry());

  // Editing finished
  m_currentItem = nullptr;
}

}  // namespace SchMatrix
