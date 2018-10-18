#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->graphicsView);
    ui->toolDockWidget->setTitleBarWidget(new QWidget());
    ui->toolDockWidget->setFixedWidth(45);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog *about = new AboutDialog;
    about->show();
}

void MainWindow::on_action_Exit_triggered()
{
    close();
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog::getOpenFileName();
}
