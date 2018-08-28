#include "defprop.h"
#include "ui_defprop.h"

DefProp::DefProp(QWidget *parent, Properties *_prop) :
        Property(parent,_prop),
        ui(new Ui::DefProp)
{
        ui->setupUi(this);
        ui->spinBox->setValue(prop->getFrameRate());
        ui->lineEdit->setText(QString::number(prop->getFrameSize().height())+"x"+QString::number(prop->getFrameSize().width()));
}

DefProp::~DefProp()
{
        delete ui;
}
