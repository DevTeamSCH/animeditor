#ifndef HORIZONTALHEADER_H
#define HORIZONTALHEADER_H

#include <QHeaderView>
#include "animationmodel.h"
#include "horizontalheadercontrols.h"

namespace SchMatrix {

class HorizontalHeader : public QHeaderView {
  Q_OBJECT

 public:
  explicit HorizontalHeader(QWidget *parent = nullptr);

  // QAbstractItemView interface
  void setModel(QAbstractItemModel *model) override;

  // QWidget interface
 protected:
  void paintEvent(QPaintEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;

 private:
  SchMatrix::HorizontalHeaderControls header;
  SchMatrix::AnimationModel *animModel;
};

}  // namespace SchMatrix

#endif  // HORIZONTALHEADER_H
