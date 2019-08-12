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
  SchMatrix::AnimationModel *m_animationModel = nullptr;
  SchMatrix::HorizontalHeader m_horizontalHeader;
  SchMatrix::TimelineMenu m_timelineMenu;
  QModelIndex m_menuIndex;
  bool m_menuRequested = false;
};

}  // namespace SchMatrix

#endif  // TIMELINEVIEW_H
