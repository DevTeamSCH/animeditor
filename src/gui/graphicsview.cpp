#include "graphicsview.h"

#include <QDebug>
#include <QSettings>
#include <QStyleOptionGraphicsItem>
#include <QTextDocument>
#include "graphicslinewidget.h"
#include "graphicspencilwidget.h"
#include "graphicstextwidget.h"
#include "keyframe.h"
#include "layer.h"
#include "symbol.h"

namespace SchMatrix {

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent) {}

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent) {
  setDragMode(RubberBandDrag);
  setBackgroundBrush(Qt::gray);
}

void GraphicsView::setModel(AnimationModel *model) {
  if (m_animationModel == model) return;

  if (model) {
    m_animationModel = model;
  }
}

void GraphicsView::updateCurrentTool(QAction *action) {
  auto name = action->objectName();

  // Disable text editing
  if (m_currentTool == Tools::TextTool && name != "actionText_Tool") {
    auto textWidget =
        qgraphicsitem_cast<SchMatrix::GraphicsTextWidget *>(m_currentItem);

    if (textWidget)
      textWidget->textItem().setTextInteractionFlags(Qt::NoTextInteraction);

    m_currentItem = nullptr;
  }

  // Disable pencil editing
  if (m_currentTool == Tools::PencilTool && name != "actionPencil_Tool") {
    auto pencilWidget =
        qgraphicsitem_cast<SchMatrix::GraphicsPencilWidget *>(m_currentItem);

    if (pencilWidget) pencilWidget->setDrawingEnabled(false);

    m_currentItem = nullptr;
  }

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
    setInteractive(false);
  }
  if (name == "actionZoom_Tool") {
    m_currentTool = Tools::ZoomTool;
    m_creationEnabled = false;
    setInteractive(false);
  }

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

  // Reset interactive
  if (m_currentTool != Tools::HandTool && m_currentTool != Tools::ZoomTool)
    setInteractive(true);
}

void GraphicsView::mousePressEvent(QMouseEvent *event) {
  QSettings settings;
  auto item = scene()->itemAt(mapToScene(event->pos()), transform());

  if (m_currentTool == Tools::PaintBucketTool) {
    if (!item) return;

    static_cast<SchMatrix::GraphicsWidget *>(item)->setBrush(
        QBrush(settings.value("MainWindow/brushColor").value<QColor>()));

    event->accept();
  } else if (m_currentTool == Tools::TextTool) {
    if (item) {  // Click inside the item
      auto textItem = qgraphicsitem_cast<QGraphicsTextItem *>(item);
      auto textWidget =
          qgraphicsitem_cast<SchMatrix::GraphicsTextWidget *>(m_currentItem);

      // auto deletion
      if (textWidget && textWidget->textItem().document()->isEmpty()) {
        m_animationModel->currentLayer()->deleteItem(textWidget);
        m_currentItem = nullptr;
        return;
      }

      if (!textItem) return;

      // Disable current text
      if (textWidget)
        textWidget->textItem().setTextInteractionFlags(Qt::NoTextInteraction);

      textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
      m_currentItem =
          static_cast<SchMatrix::GraphicsTextWidget *>(textItem->parentItem());
      QGraphicsView::mousePressEvent(event);
    } else {  // Click outside
      if (m_currentItem) {
        auto textWidget =
            qgraphicsitem_cast<SchMatrix::GraphicsTextWidget *>(m_currentItem);

        if (!textWidget) return;

        // auto deletion
        if (textWidget->textItem().document()->isEmpty()) {
          m_animationModel->currentLayer()->deleteItem(textWidget);
          m_currentItem = nullptr;
          return;
        }

        textWidget->resize(textWidget->textItem().boundingRect().size());
        textWidget->textItem().setTextInteractionFlags(Qt::NoTextInteraction);

        m_currentItem = nullptr;
        QGraphicsView::mousePressEvent(event);
      } else {
        auto layer = m_animationModel->currentLayer();
        auto pos = mapToScene(event->pos());
        auto item = SchMatrix::GraphicsWidget::Create(m_currentItemType,
                                                      pos.x(), pos.y(), 0, 0);
        auto textWidget =
            qgraphicsitem_cast<SchMatrix::GraphicsTextWidget *>(item);

        item->setPen(
            QPen(settings.value("MainWindow/penColor").value<QColor>(), 0));
        item->setBrush(
            QBrush(settings.value("MainWindow/brushColor").value<QColor>()));
        textWidget->textItem().setDefaultTextColor(textWidget->pen().color());
        layer->addItem(item);
      }
    }
  } else if (m_currentTool == Tools::PencilTool) {
    if (item) {  // Click inside the item
      auto pencilWidget =
          qgraphicsitem_cast<SchMatrix::GraphicsPencilWidget *>(item);

      if (!pencilWidget) return;

      auto currenPencilWidget =
          qgraphicsitem_cast<SchMatrix::GraphicsPencilWidget *>(m_currentItem);

      // Disable current item drawing
      if (currenPencilWidget) currenPencilWidget->setDrawingEnabled(false);

      m_currentItem = pencilWidget;
      pencilWidget->setDrawingEnabled(true);
      QGraphicsView::mousePressEvent(event);
    } else {  // Click outside
      if (m_currentItem) {
        auto pencilWidget =
            qgraphicsitem_cast<SchMatrix::GraphicsPencilWidget *>(
                m_currentItem);

        if (!pencilWidget) return;

        pencilWidget->setDrawingEnabled(false);

        m_currentItem = nullptr;
        QGraphicsView::mousePressEvent(event);
      } else {
        auto layer = m_animationModel->currentLayer();
        auto size = scene()->sceneRect().size();
        auto pos = mapToScene(event->pos());
        SchMatrix::GraphicsWidget *pencilWidget = nullptr;

        // Create at fix position
        if (sceneRect().contains(pos)) {
          pencilWidget = SchMatrix::GraphicsWidget::Create(
              m_currentItemType, 0, 0, size.width(), size.height());
        } else {  // Create at pos
          pencilWidget = SchMatrix::GraphicsWidget::Create(
              m_currentItemType, pos.x(), pos.y(), size.width(), size.height());
        }

        pencilWidget->setPen(
            QPen(settings.value("MainWindow/penColor").value<QColor>(), 0));
        pencilWidget->setBrush(
            QBrush(settings.value("MainWindow/brushColor").value<QColor>()));
        layer->addItem(pencilWidget);
      }
    }
  } else {
    QGraphicsView::mousePressEvent(event);
  }
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event) {
  QSettings settings;

  if (m_creationEnabled == false || !(event->buttons() & Qt::LeftButton) ||
      m_currentTool == Tools::TextTool || m_currentTool == Tools::PencilTool) {
    QGraphicsView::mouseMoveEvent(event);
    return;
  }

  auto pos = mapToScene(event->pos());
  auto layer = m_animationModel->currentLayer();

  // Creation
  if (!m_currentItem) {
    m_currentItem =
        GraphicsWidget::Create(m_currentItemType, pos.x(), pos.y(), 0, 0);
    m_currentItem->setPen(
        QPen(settings.value("MainWindow/penColor").value<QColor>(), 0));
    m_currentItem->setBrush(
        QBrush(settings.value("MainWindow/brushColor").value<QColor>()));

    layer->addItem(m_currentItem);
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

  event->accept();
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event) {
  QGraphicsView::mouseReleaseEvent(event);

  if (!m_currentItem) return;

  // Skip currently edited text
  if (m_currentTool == Tools::TextTool && m_currentItem) return;
  if (m_currentTool == Tools::PencilTool && m_currentItem) return;

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

  // Update pos, size after editing
  layer->currentKeyframe()->assignProperty(m_currentItem, "pos",
                                           m_currentItem->pos());
  layer->currentKeyframe()->assignProperty(m_currentItem, "size",
                                           m_currentItem->size());

  // Editing finished
  m_currentItem = nullptr;
}

void SchMatrix::GraphicsView::wheelEvent(QWheelEvent *event) {
  if (event->modifiers() & Qt::CTRL) {
    const qreal detail =
        QStyleOptionGraphicsItem::levelOfDetailFromTransform(transform());
    const qreal factor = 1.1;

    setTransformationAnchor(AnchorUnderMouse);

    // Zoom in
    if ((detail < 50) && (event->angleDelta().y() > 0)) scale(factor, factor);

    // Zoom out
    if ((detail > 1) && (event->angleDelta().y() < 0))
      scale((1 / factor), (1 / factor));

    event->accept();
  } else {
    QGraphicsView::wheelEvent(event);
  }
}

void GraphicsView::keyPressEvent(QKeyEvent *event) {
  QGraphicsView::keyPressEvent(event);

  if (m_currentTool == Tools::SelectionTool ||
      m_currentTool == Tools::TransformTool) {
    auto items = scene()->selectedItems();
    auto key = event->key();

    if (items.empty() == false) {
      // Item deletion by key
      if (key == Qt::Key_Delete || key == Qt::Key_Backspace) {
        for (auto item : items) {
          m_animationModel->currentLayer()->deleteItem(
              static_cast<SchMatrix::GraphicsWidget *>(item));
        }

        return;
      }

      // Set step unit
      qreal x = (event->modifiers() & Qt::SHIFT) ? 5 : 1;
      qreal y = x;

      for (auto item : items) {
        if (key == Qt::Key_Left) {
          item->moveBy(-x, 0);
        }
        if (key == Qt::Key_Right) {
          item->moveBy(x, 0);
        }
        if (key == Qt::Key_Up) {
          item->moveBy(0, -y);
        }
        if (key == Qt::Key_Down) {
          item->moveBy(0, y);
        }
      }
    }
  }
}

void GraphicsView::drawBackground(QPainter *painter, const QRectF &rect) {
  QGraphicsView::drawBackground(painter, rect);

  painter->setPen(QPen(Qt::black, 0));
  painter->setBrush(Qt::white);

  painter->drawRect(sceneRect());
}

}  // namespace SchMatrix
