#include "textprop.h"
#include "ui_textprop.h"

TextProp::TextProp(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::TextProp)
{
        ui->setupUi(this);
}

TextProp::~TextProp()
{
        delete ui;
}
