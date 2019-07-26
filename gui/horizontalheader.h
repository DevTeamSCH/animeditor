#ifndef HORIZONTALHEADER_H
#define HORIZONTALHEADER_H

#include <QHeaderView>
#include <QTableView>
#include "animationmodel.h"
#include "horizontalheadercontrols.h"

namespace SchMatrix {

class HorizontalHeader : public QHeaderView {
  Q_OBJECT

 public:
  explicit HorizontalHeader(QWidget *parent = nullptr);

  // QAbstractItemView interface
  void setModel(QAbstractItemModel *model) override;

 public slots:
  void updateFrame(int frame);

  // QWidget interface
 protected:
  void paintEvent(QPaintEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;

 private:
  SchMatrix::HorizontalHeaderControls header;
  SchMatrix::AnimationModel *animModel;
  QTableView *table;
};

}  // namespace SchMatrix

#endif  // HORIZONTALHEADER_H
