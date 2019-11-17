#include "framedelegate.h"

#include <QPainter>
#include "keyframe.h"

namespace SchMatrix {

FrameDelegate::FrameDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void FrameDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const {
  auto col = index.column();

  auto &optionRect = option.rect;
  auto keyY = optionRect.height() / 2 - 5;

  painter->save();

  painter->setPen(Qt::NoPen);
  painter->setBrush(QColor("#d6d6d6"));  // Non potential frame color
  painter->setRenderHint(QPainter::Antialiasing, true);

  switch (index.data().toInt()) {
    case SchMatrix::Frame:
      painter->drawRect(option.rect);
      break;
    case SchMatrix::EndOfFrame:
      painter->drawRect(option.rect);

      painter->setBrush(Qt::NoBrush);
      painter->setPen(Qt::black);
      painter->drawRect(optionRect.center().x() - 1,
                        optionRect.center().y() + optionRect.height() / 2 - 12,
                        5, 10);
      break;
    case SchMatrix::Key:
      painter->drawRect(option.rect);

      painter->setPen(Qt::black);
      painter->setBrush(Qt::black);
      painter->drawEllipse(optionRect.center() + QPoint(1, keyY), 3, 3);
      break;
    case SchMatrix::BlankKey:
      painter->drawRect(option.rect);

      painter->setPen(Qt::black);
      painter->setBrush(Qt::NoBrush);
      painter->drawEllipse(optionRect.center() + QPoint(1, keyY), 3, 3);
      break;
    case SchMatrix::PotentialFrame:
      painter->setPen(QPen(QColor("#d9d9d9"), 2));
      painter->setBrush(((col + 1) % 5 == 0) ? QColor("#e0e0e0")
                                             : QColor("#e8e8e8"));
      painter->drawRect(option.rect);
      break;
    case SchMatrix::TweenedFrame:
      painter->drawRect(option.rect);

      painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
      painter->drawLine(optionRect.x(),
                        optionRect.y() + optionRect.height() - 5,
                        optionRect.x() + optionRect.width(),
                        optionRect.y() + optionRect.height() - 5);
      break;
  }

  auto selectionBrush = option.palette.highlight();
  auto selectionColor = selectionBrush.color();
  selectionColor.setAlpha(128);
  selectionBrush.setColor(selectionColor);

  if (option.state & QStyle::State_Selected)
    painter->fillRect(option.rect, selectionBrush);

  painter->restore();
}

QSize SchMatrix::FrameDelegate::sizeHint(const QStyleOptionViewItem &option,
                                         const QModelIndex &) const {
  return option.rect.size();
}

}  // namespace SchMatrix
