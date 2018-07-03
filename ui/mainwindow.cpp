#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "colorindicator.h"
#include "colorwheel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
         ui->setupUi(this);
        ColorIndicator* ci=new ColorIndicator();
        ColorWheel* cw=new ColorWheel();
        connect(cw,SIGNAL(colorChanged(QColor)),ci,SLOT(updateColor(QColor)));

         //ui->centralWidget->layout()->addWidget(ci);

         QWidget* multiWidget= new QWidget();
         QVBoxLayout* layout=new QVBoxLayout();
         layout->addWidget(cw);
         layout->addWidget(ci);
         multiWidget->setLayout(layout);
         ui->rightPanelDock->setMinimumSize(250,100);
         ui->rightPanelDock->setWidget(multiWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
