#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "frameelement.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->frameEditLayout->setMargin(2);
    for(int i=0;i<15;i++){
        for(int j=0;j<13;j++)
             ui->frameEditLayout->addWidget(new FrameElement(this),i,j);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
