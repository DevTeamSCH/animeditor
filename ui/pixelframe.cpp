#include "pixelframe.h"
#include "ui_pixelframe.h"
#include "frameelement.h"

#include <QScrollArea>
#include <QGridLayout>

PixelFrame::PixelFrame(unsigned sizeX, unsigned sizeY, QWidget *parent) : QWidget(parent), ui(new Ui::PixelFrame)
{
        drawColor=QColor(0,0,0);
        x=sizeX;
        y=sizeY;

        QGridLayout *frameEditLayout=new QGridLayout();
        ui->setupUi(this);
        QWidget *client = new QWidget;
        client->setLayout(frameEditLayout);
        QWidget *placeholder1 = new QWidget;
        QWidget *placeholder2 = new QWidget;



        placeholder1->setMinimumSize(100,500);
        placeholder2->setMinimumSize(100,500);
        QHBoxLayout *frameContainer=new QHBoxLayout();
        frameContainer->setMargin(0);

        setLayout(frameContainer);
        layout()->addWidget(placeholder1);
        layout()->addWidget(client);
        layout()->addWidget(placeholder2);

        frameEditLayout->setMargin(2);
        frameEditLayout->setVerticalSpacing(12);
        for(unsigned i=0;i<sizeX;i++){
                for(unsigned j=0;j<sizeY;j++)
                        frameEditLayout->addWidget(new FrameElement(this,i,j),i,j);
        }
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
/*
QSize PixelFrame::sizeHint() const{
        return QSize((this->childAt(0,0)->size().width()+2)*x,(this->childAt(0,0)->size().height()*2*y));
}
*/
