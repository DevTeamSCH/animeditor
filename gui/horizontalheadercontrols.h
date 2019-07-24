#ifndef HORIZONTALHEADERCONTROLS_H
#define HORIZONTALHEADERCONTROLS_H

#include <QWidget>

namespace Ui {
class HorizontalHeaderControls;
}

namespace SchMatrix {

class HorizontalHeaderControls : public QWidget {
  Q_OBJECT

 public:
  explicit HorizontalHeaderControls(QWidget *parent = nullptr);
  ~HorizontalHeaderControls();

 private:
  Ui::HorizontalHeaderControls *ui;
};

}  // namespace SchMatrix

#endif  // HORIZONTALHEADERCONTROLS_H
