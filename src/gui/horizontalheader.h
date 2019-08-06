#ifndef HORIZONTALHEADER_H
#define HORIZONTALHEADER_H

#include <QHeaderView>
#include <QTableView>
#include "horizontalheadercontrols.h"

namespace SchMatrix {

class AnimationModel;

class HorizontalHeader : public QHeaderView {
  Q_OBJECT

 public:
  explicit HorizontalHeader(QWidget *parent = nullptr);

  // QAbstractItemView interface
  void setModel(QAbstractItemModel *model) override;

 public slots:
  void updateFrame(int newFrame, int oldFrame);

  // QWidget interface
 protected:
  void paintEvent(QPaintEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;

 private:
  SchMatrix::HorizontalHeaderControls m_headerControls;
  SchMatrix::AnimationModel *m_animationModel = nullptr;
  QTableView *m_timelineView;
};

}  // namespace SchMatrix

#endif  // HORIZONTALHEADER_H
