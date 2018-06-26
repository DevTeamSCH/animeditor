#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pixelframe.h"
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::MainWindow)
{
        ui->setupUi(this);
        ui->centralWidget->layout()->setMargin(0);
        ui->centralWidget->layout()->addWidget(new PixelFrame(16,13));

}

MainWindow::~MainWindow()
{
        delete ui;
}
