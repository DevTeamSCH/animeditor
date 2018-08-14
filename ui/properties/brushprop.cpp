#include "brushprop.h"
#include "ui_brushprop.h"


BrushProp::BrushProp(QWidget *parent) :
        Property(parent),
        ui(new Ui::BrushProp)
{
        ui->setupUi(this);
}

BrushProp::~BrushProp()
{
        delete ui;
}
