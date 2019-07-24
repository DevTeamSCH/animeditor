#include "horizontalheadercontrols.h"
#include "ui_horizontalheadercontrols.h"

namespace SchMatrix {

HorizontalHeaderControls::HorizontalHeaderControls(QWidget *parent)
    : QWidget(parent), ui(new Ui::HorizontalHeaderControls) {
  ui->setupUi(this);
}

HorizontalHeaderControls::~HorizontalHeaderControls() { delete ui; }

}  // namespace SchMatrix
