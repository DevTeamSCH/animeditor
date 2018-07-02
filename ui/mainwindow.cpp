#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "colorwheel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
         ui->setupUi(this);
         QWidget* multiWidget= new QWidget();
         QVBoxLayout* layout=new QVBoxLayout();
         layout->addWidget(new ColorWheel());
         multiWidget->setLayout(layout);
         ui->rightPanelDock->setMinimumSize(250,100);
         ui->rightPanelDock->setWidget(multiWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
