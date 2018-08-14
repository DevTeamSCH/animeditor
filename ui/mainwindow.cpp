#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "pixelframe.h"
#include <QGroupBox>

#include "colorindicator.h"
#include "colorwheel.h"
#include "toolbar.h"
#include "properties.h"

//Constructs a deafault window with 16*13 pixelframe, color picker, tools etc...

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), pf(nullptr),ui(new Ui::MainWindow)
{
        ui->setupUi(this);
        setFrame(13,16);
        setupCentralWidget();
        setupRightSide();

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
                //centralWidget()->layout()->removeWidget(pf);
                delete pf;
        }
        pf=new PixelFrame(x,y);
      //  centralWidget()->layout()->addWidget(pf);
}

void MainWindow::setupCentralWidget(){

        QWidget *client = new QWidget;
        QWidget *placeholder1 = new QWidget;
        QWidget *placeholder2 = new QWidget;

        placeholder1->setMinimumSize(100,500);
        placeholder2->setMinimumSize(100,500);

        centralWidget()->layout()->setMargin(0);
        centralWidget()->layout()->addWidget(placeholder1);
        centralWidget()->layout()->addWidget(client);
        centralWidget()->layout()->addWidget(placeholder2);

        client->setLayout(new QVBoxLayout());
        client->layout()->addWidget(new QWidget());
        client->layout()->addWidget(pf);
        client->layout()->addWidget(new QWidget());

}

void MainWindow::setupRightSide(){
        ColorIndicator* ci=new ColorIndicator();
        ColorWheel* cw=new ColorWheel();
        Toolbar* tb=new Toolbar();
        Properties* prop=new Properties();

        connect(cw,SIGNAL(colorChanged(QColor)),ci,SLOT(updateColor(QColor)));
        connect(cw,SIGNAL(colorChanged(QColor)),pf,SLOT(updateColor(QColor)));
        connect(ci,SIGNAL(colorChanged(QColor)),cw,SLOT(setColor(QColor)));
        connect(tb,SIGNAL(toolChanged(ToolState)),pf,SLOT(setTool(ToolState)));
        connect(tb,SIGNAL(toolChanged(ToolState)),prop,SLOT(toolChanged(ToolState)));

        QVBoxLayout* rightSideLayout=new QVBoxLayout();
        rightSideLayout->addWidget(cw);
        rightSideLayout->addWidget(ci);

        QWidget* multiWidget= new QWidget();
        QGridLayout* multiLayout= new QGridLayout();


        QWidget* rightWidget=new QWidget();
        multiLayout->addWidget(tb,1,0,5,1);
        multiLayout->addWidget(rightWidget,1,1,5,5);
        multiLayout->addWidget(prop,6,1,5,5);
        multiWidget->setLayout(multiLayout);

        rightWidget->setLayout(rightSideLayout);
        ui->rightPanelDock->setMinimumSize(300,250);
        ui->rightPanelDock->setWidget(multiWidget);
}
