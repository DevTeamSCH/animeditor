#include "brushprop.h"
#include "ui_brushprop.h"


BrushProp::BrushProp(QWidget *parent, Properties *_prop) :
        Property(parent,_prop),
        ui(new Ui::BrushProp)
{
        ui->setupUi(this);
        ui->spinBox->setValue(prop->getBrush());
}

BrushProp::~BrushProp()
{
        delete ui;
}

void BrushProp::on_spinBox_valueChanged(int arg1)
{
    prop->setBrush(arg1);
}
