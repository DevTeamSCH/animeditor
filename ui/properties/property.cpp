#include "property.h"
#include "ui_property.h"

Property::Property(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Property)
{
        ui->setupUi(this);
}

Property::~Property()
{
        delete ui;
}
