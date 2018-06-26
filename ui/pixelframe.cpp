#include "pixelframe.h"
#include "ui_pixelframe.h"
#include "frameelement.h"

#include <QScrollArea>
#include <QGridLayout>

PixelFrame::PixelFrame(unsigned sizeX, unsigned sizeY, QWidget *parent) : QWidget(parent), ui(new Ui::PixelFrame)
{
        QGridLayout *frameEditLayout=new QGridLayout();
        ui->setupUi(this);
        QWidget *client = new QWidget;
        QScrollArea *scrollArea = new QScrollArea;
        scrollArea->setWidgetResizable(true);
        scrollArea->setWidget(client);
        client->setLayout(frameEditLayout);

        setLayout(new QVBoxLayout);
        layout()->addWidget(scrollArea);

        frameEditLayout->setMargin(2);
        for(unsigned i=0;i<sizeX;i++){
                for(unsigned j=0;j<sizeY;j++)
                        frameEditLayout->addWidget(new FrameElement(this),i,j);
        }
}

PixelFrame::~PixelFrame()
{
        delete ui;
}
