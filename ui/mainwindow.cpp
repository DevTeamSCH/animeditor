#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "pixelframe.h"
#include <QScrollArea>

#include "colorindicator.h"
#include "colorwheel.h"

//Constructs a deafault window with 16*13 pixelframe, color picker, tools etc...

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), pf(nullptr),ui(new Ui::MainWindow)
{
        ui->setupUi(this);

        ui->centralWidget->layout()->setMargin(0);
        setFrame(13,16);

        ColorIndicator* ci=new ColorIndicator();
        ColorWheel* cw=new ColorWheel();
        connect(cw,SIGNAL(colorChanged(QColor)),ci,SLOT(updateColor(QColor)));
        connect(cw,SIGNAL(colorChanged(QColor)),pf,SLOT(updateColor(QColor)));
        connect(ci,SIGNAL(colorChanged(QColor)),cw,SLOT(setColor(QColor)));

         QWidget* multiWidget= new QWidget();
         QVBoxLayout* rightSideLayout=new QVBoxLayout();
         rightSideLayout->addWidget(cw);
         rightSideLayout->addWidget(ci);
         multiWidget->setLayout(rightSideLayout);
         ui->rightPanelDock->setMinimumSize(250,100);
         ui->rightPanelDock->setWidget(multiWidget);

}

MainWindow::~MainWindow()
{
        delete pf;
        delete ui;
}

//Sets the number of windows in the central area in the PixelFrame

void MainWindow::setFrame(unsigned x,unsigned y){
        if(pf!=nullptr)
        {
                centralWidget()->layout()->removeWidget(pf);
                delete pf;
        }
        pf=new PixelFrame(x,y);
        centralWidget()->layout()->addWidget(pf);
}

