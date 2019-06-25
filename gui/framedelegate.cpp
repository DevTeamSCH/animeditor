#include "framedelegate.h"

namespace SchMatrix {

FrameDelegate::FrameDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void SchMatrix::FrameDelegate::paint(QPainter *painter,
                                     const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const {}

QSize SchMatrix::FrameDelegate::sizeHint(const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const {
  return option.rect.size();
}

}  // namespace SchMatrix
