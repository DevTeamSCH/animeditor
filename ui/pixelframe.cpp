#include "pixelframe.h"
#include "ui_pixelframe.h"
#include "frameelement.h"

#include <iostream>

#include <QGridLayout>

PixelFrame::PixelFrame(unsigned sizeX, unsigned sizeY, QWidget *parent) : QWidget(parent), ui(new Ui::PixelFrame)
{
        drawColor=QColor(0,0,0);
        x=sizeX;
        y=sizeY;

        ui->setupUi(this);

        QGridLayout *frameEditLayout=new QGridLayout();

        setLayout(frameEditLayout);
        frameEditLayout->setMargin(2);
        frameEditLayout->setVerticalSpacing(12);
        for(unsigned i=0;i<sizeX;i++){
                for(unsigned j=0;j<sizeY;j++)
                        frameEditLayout->addWidget(new FrameElement(this,i,j),i,j);
        }
        frameEditLayout->setHorizontalSpacing(3);
}

PixelFrame::~PixelFrame()
{
        delete ui;
}

void PixelFrame::updateColor(QColor color){
        drawColor=color;
}

QColor PixelFrame::getDrawColor(){
        return drawColor;
}

QSize PixelFrame::sizeHint() const{

        return QSize((layout()->itemAt(1)->widget()->width()+1)*x,layout()->itemAt(1)->widget()->height()*2*y);
}


