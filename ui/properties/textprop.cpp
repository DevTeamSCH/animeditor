#include "textprop.h"
#include "ui_textprop.h"

TextProp::TextProp(QWidget *parent, Properties *prop) :
        Property(parent,prop),
        ui(new Ui::TextProp)
{
        ui->setupUi(this);
}

TextProp::~TextProp()
{
        delete ui;
}
