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
        emit sizeHasSet(QSize(x,y));
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

void PixelFrame::setTool(ToolState tools){
        ts=tools;
        QPixmap pixm;

        switch(ts){
        case Arrow:
                setCursor(Qt::ArrowCursor);
                break;
        case Brush:
                pixm=QPixmap(":/images/brushicon");
                setCursor(pixm);
                break;
        case Pipette:
                pixm= QPixmap(":/images/pipette");
                setCursor(pixm);
                break;
        default:
                setCursor(Qt::CrossCursor);
                break;
        }
}

