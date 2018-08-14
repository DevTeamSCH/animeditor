#include "properties.h"
#include "ui_properties.h"
#include <QVBoxLayout>
#include "properties/property.h"
#include "properties/defprop.h"
#include "properties/drawprop.h"
#include "properties/brushprop.h"

Properties::Properties(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Properties)
{
        setLayout(new QVBoxLayout());
        layout()->addWidget(actProp);
        ui->setupUi(this);

}

Properties::~Properties()
{
        delete ui;
}

void Properties::toolChanged(ToolState state){
        switch(state){
                case Brush: layout()->removeWidget(actProp);
                            delete actProp;
                            actProp=new BrushProp();
                            layout()->addWidget(actProp);
                            break;
                case Line: layout()->removeWidget(actProp);
                            delete actProp;
                            actProp=new BrushProp();
                            layout()->addWidget(actProp);
                            break;
                case Rectangle: layout()->removeWidget(actProp);
                                delete actProp;
                                actProp=new DrawProp();
                                layout()->addWidget(actProp);
                                 break;
                case Ellipse: layout()->removeWidget(actProp);
                                delete actProp;
                                 actProp=new DrawProp();
                                layout()->addWidget(actProp);
                                 break;
                default: layout()->removeWidget(actProp);
                         delete actProp;
                         actProp=new DefProp();
                         layout()->addWidget(actProp);
                         break;
        }
}
