#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "frameelement.h"
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    QGridLayout *frameEditLayout=new QGridLayout();
    ui->setupUi(this);
    QWidget *client = new QWidget;
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(client);
    client->setLayout(frameEditLayout);

    ui->centralWidget->setLayout(new QVBoxLayout);
    ui->centralWidget->layout()->addWidget(scrollArea);

    frameEditLayout->setMargin(2);
    for(int i=0;i<13;i++){
        for(int j=0;j<16;j++)
             frameEditLayout->addWidget(new FrameElement(this),i,j);
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}
