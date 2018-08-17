#include "drawprop.h"
#include "ui_drawprop.h"

DrawProp::DrawProp(QWidget *parent, Properties *prop) :
        Property(parent,prop),
        ui(new Ui::DrawProp)
{
        ui->setupUi(this);
}

DrawProp::~DrawProp()
{
        delete ui;
}
