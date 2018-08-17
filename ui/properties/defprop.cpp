#include "defprop.h"
#include "ui_defprop.h"

DefProp::DefProp(QWidget *parent, Properties *_prop) :
        Property(parent,_prop),
        ui(new Ui::DefProp)
{
        ui->setupUi(this);
}

DefProp::~DefProp()
{
        delete ui;
}
