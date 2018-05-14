#include "frameelement.h"
#include "ui_frameelement.h"
#include <QGridLayout>

FrameElement::FrameElement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrameElement)
{
    QGridLayout* layout=new QGridLayout();
    layout->setSpacing(1);
    layout->setMargin(2);

    setMaximumSize(80,80);
    setMinimumHeight(20);

    for(int i=0;i<4;i++){
        pixels.append(new PixelWidget(this->height()/2,this));
        layout->addWidget(pixels[i],i/2,i%2);
    }

    this->setLayout(layout);
    ui->setupUi(this);
}


void FrameElement::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);
    QWidget::heightForWidth(this->height());

}

FrameElement::~FrameElement()
{
    delete ui;
}
