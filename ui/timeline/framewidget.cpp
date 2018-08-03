#include "framewidget.h"
#include "ui_framewidget.h"

frameWidget::frameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frameWidget)
{
    ui->setupUi(this);
}

frameWidget::~frameWidget()
{
    delete ui;
}
