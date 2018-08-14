#include "defprop.h"
#include "ui_defprop.h"

DefProp::DefProp(QWidget *parent) :
        Property(parent),
        ui(new Ui::DefProp)
{
        ui->setupUi(this);
}

DefProp::~DefProp()
{
        delete ui;
}
