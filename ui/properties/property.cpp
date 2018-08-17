#include "property.h"
#include "ui_property.h"

Property::Property(QWidget *parent, Properties *p) :
        QWidget(parent),
        ui(new Ui::Property)
{
        prop=p;
        ui->setupUi(this);
}

Property::~Property()
{
        delete ui;
}
