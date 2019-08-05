#include "graphicstextwidget.h"

namespace SchMatrix {

GraphicsTextWidget::GraphicsTextWidget(const QString &string,
                                       QGraphicsItem *parent,
                                       Qt::WindowFlags wFlags)
    : SchMatrix::GraphicsWidget(parent, wFlags), text(string, this) {
  text.setTextInteractionFlags(Qt::TextEditorInteraction);
}

int GraphicsTextWidget::type() const { return Type; }

}  // namespace SchMatrix
