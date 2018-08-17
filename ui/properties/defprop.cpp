#include "defprop.h"
#include "ui_defprop.h"

DefProp::DefProp(QWidget *parent, Properties *prop) :
        Property(parent,prop),
        ui(new Ui::DefProp)
{
        ui->setupUi(this);
}

DefProp::~DefProp()
{
        delete ui;
}
