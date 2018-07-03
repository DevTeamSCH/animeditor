#include "mainwindow.h"
#include "ui_mainwindow.h"
<<<<<<< HEAD
#include "pixelframe.h"
#include <QScrollArea>
=======
#include "colorindicator.h"
#include "colorwheel.h"
>>>>>>> color_copy

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::MainWindow)
{
<<<<<<< HEAD
        ui->setupUi(this);
        ui->centralWidget->layout()->setMargin(0);
        ui->centralWidget->layout()->addWidget(new PixelFrame(16,13));

=======
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
>>>>>>> color_copy
}

MainWindow::~MainWindow()
{
        delete ui;
}
