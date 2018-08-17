#include "brushprop.h"
#include "ui_brushprop.h"


BrushProp::BrushProp(QWidget *parent, Properties *prop) :
        Property(parent,prop),
        ui(new Ui::BrushProp)
{
        ui->setupUi(this);
}

BrushProp::~BrushProp()
{
        delete ui;
}
