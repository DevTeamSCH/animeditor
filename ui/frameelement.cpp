#include "frameelement.h"
#include "ui_frameelement.h"
#include <QGridLayout>

FrameElement::FrameElement(QWidget *parent) :QWidget(parent), ui(new Ui::FrameElement)
{
        QGridLayout* layout=new QGridLayout();
        layout->setSpacing(1);
        layout->setMargin(0);

        setMaximumSize(31,31);
        setMinimumSize(31,31);

        for(int i=0;i<4;i++){
                pixels.append(new PixelWidget(this));
                layout->addWidget(pixels[i],i/2,i%2);
        }

        this->setLayout(layout);
        ui->setupUi(this);
}


FrameElement::~FrameElement()
{
        delete ui;
}
