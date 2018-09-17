#include "lineprop.h"
#include "ui_lineprop.h"

LineProp::LineProp(QWidget *parent, Properties *_prop) :
	Property(parent, _prop),
	ui(new Ui::LineProp)
{
	ui->setupUi(this);
	ui->spinBox->setValue(prop->getLine());
}

LineProp::~LineProp()
{
	delete ui;
}

void LineProp::on_spinBox_valueChanged(int arg1)
{
	prop->setLine(arg1);
}
