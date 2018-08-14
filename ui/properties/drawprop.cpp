#include "drawprop.h"
#include "ui_drawprop.h"

DrawProp::DrawProp(QWidget *parent) :
        Property(parent),
        ui(new Ui::DrawProp)
{
        ui->setupUi(this);
}

DrawProp::~DrawProp()
{
        delete ui;
}
