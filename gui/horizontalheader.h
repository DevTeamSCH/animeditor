#ifndef HORIZONTALHEADER_H
#define HORIZONTALHEADER_H

#include <QHeaderView>

namespace SchMatrix {

class HorizontalHeader : public QHeaderView {
  Q_OBJECT

 public:
  explicit HorizontalHeader(QWidget *parent = nullptr);
};

}  // namespace SchMatrix

#endif  // HORIZONTALHEADER_H
