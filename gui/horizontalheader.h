#ifndef HORIZONTALHEADER_H
#define HORIZONTALHEADER_H

#include <QHeaderView>
#include "horizontalheadercontrols.h"

namespace SchMatrix {

class HorizontalHeader : public QHeaderView {
  Q_OBJECT

 public:
  explicit HorizontalHeader(QWidget *parent = nullptr);

  // QWidget interface
 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  SchMatrix::HorizontalHeaderControls header;
};

}  // namespace SchMatrix

#endif  // HORIZONTALHEADER_H
