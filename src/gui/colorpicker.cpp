#include "colorpicker.h"

#include <QColorDialog>
#include <QMouseEvent>
#include <QPainter>

namespace SchMatrix {

ColorPicker::ColorPicker(const QColor &initial, QWidget *parent)
    : QFrame(parent), m_currentColor(initial) {
  setFrameShape(QFrame::Box);
}

QSize ColorPicker::minimumSizeHint() const { return QSize(24, 24); }

QColor ColorPicker::currentColor() const { return m_currentColor; }

void ColorPicker::setCurrentColor(const QColor &currentColor) {
  m_currentColor = currentColor;
}

void ColorPicker::mousePressEvent(QMouseEvent *event) {
  if (!(event->buttons() & Qt::LeftButton)) return;

  QColor color = QColorDialog::getColor(m_currentColor, this);

  if (color.isValid()) {
    m_currentColor = color;
    emit currentColorChanged(color);
    update();
  }
}

void ColorPicker::paintEvent(QPaintEvent *event) {
  QFrame::paintEvent(event);

  QPainter painter(this);

  painter.setPen(Qt::NoPen);
  painter.setBrush(m_currentColor);
  painter.drawRect(contentsRect());
}

}  // namespace SchMatrix
