#include "properties.h"
#include "ui_properties.h"
#include <QVBoxLayout>
#include "properties/property.h"
#include "properties/defprop.h"
#include "properties/drawprop.h"
#include "properties/brushprop.h"
#include "properties/textprop.h"

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
        delete actProp;
}

void Properties::toolChanged(ToolState state){
        switch(state){
                case Brush: layout()->removeWidget(actProp);
                            delete actProp;
                            actProp=new BrushProp(this,this);
                            layout()->addWidget(actProp);
                            break;
                case Line: layout()->removeWidget(actProp);
                            delete actProp;
                            actProp=new BrushProp(this,this);
                            layout()->addWidget(actProp);
                            break;
                case Rectangle: layout()->removeWidget(actProp);
                                delete actProp;
                                actProp=new DrawProp(this,this);
                                layout()->addWidget(actProp);
                                 break;
                case Ellipse: layout()->removeWidget(actProp);
                                delete actProp;
                                 actProp=new DrawProp(this,this);
                                layout()->addWidget(actProp);
                                 break;
                case Text: layout()->removeWidget(actProp);
                            delete actProp;
                            actProp=new TextProp(this,this);
                            layout()->addWidget(actProp);
                            break;
                default: layout()->removeWidget(actProp);
                         delete actProp;
                         actProp=new DefProp(this,this);
                         layout()->addWidget(actProp);
                         break;
        }
}

int Properties::getBrush(){
        return brushSize;
}
void Properties::setBrush(int siz){
        brushSize=siz;
}

int Properties::getFrameRate(){}
int Properties::getFrameSize(){}
int Properties::getLine(){}
void Properties::setLine(int){}
