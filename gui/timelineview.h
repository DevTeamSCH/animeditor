#ifndef TIMELINEVIEW_H
#define TIMELINEVIEW_H

#include <QTableView>
#include "animationmodel.h"

namespace SchMatrix {

class TimelineView : public QTableView {
  Q_OBJECT

 public:
  explicit TimelineView(QWidget *parent = nullptr);

  // QWidget interface
 protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;

 private:
  SchMatrix::AnimationModel *animModel;

  // QAbstractItemView interface
 public:
  void setModel(QAbstractItemModel *model) override;
};

}  // namespace SchMatrix

#endif  // TIMELINEVIEW_H
