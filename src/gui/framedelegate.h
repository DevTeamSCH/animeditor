#ifndef FRAMEDELEGATE_H
#define FRAMEDELEGATE_H

#include <QStyledItemDelegate>

namespace SchMatrix {

class FrameDelegate : public QStyledItemDelegate {
  Q_OBJECT

 public:
  explicit FrameDelegate(QObject *parent = nullptr);

  // QAbstractItemDelegate interface
  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const override;
  QSize sizeHint(const QStyleOptionViewItem &option,
                 const QModelIndex &index) const override;
};

}  // namespace SchMatrix

#endif  // FRAMEDELEGATE_H
