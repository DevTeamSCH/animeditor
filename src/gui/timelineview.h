#ifndef TIMELINEVIEW_H
#define TIMELINEVIEW_H

#include <QModelIndex>
#include <QTableView>
#include "horizontalheader.h"
#include "timelinemenu.h"

namespace SchMatrix {

class AnimationModel;

class TimelineView : public QTableView {
  Q_OBJECT

 public:
  explicit TimelineView(QWidget *parent = nullptr);

  // QWidget interface
 protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void contextMenuEvent(QContextMenuEvent *event) override;

 public slots:
  void updateFrame(int newFrame, int oldFrame);

  // QAbstractItemView interface
 public:
  void setModel(QAbstractItemModel *model) override;

 private slots:
  void handleMenu(QAction *action);

 private:
  SchMatrix::AnimationModel *animModel;
  SchMatrix::HorizontalHeader header;
  SchMatrix::TimelineMenu timelineMenu;
  QModelIndex index;
};

}  // namespace SchMatrix

#endif  // TIMELINEVIEW_H
