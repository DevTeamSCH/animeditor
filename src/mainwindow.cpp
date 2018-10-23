#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "matrixscene.h"

#include <QFileDialog>
#include <QtGui>
#include <QtWidgets>

// set static variables
QColor MainWindow::BGColor = Qt::white;
QColor MainWindow::FGColor = Qt::white;
bool MainWindow::isPaintWindow = false;
bool MainWindow::isFGSelected = true;
bool MainWindow::isMousePressed = false;
MainWindow::tool MainWindow::activeTool = Pointer;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolDockWidget->setTitleBarWidget(new QWidget());
    ui->toolDockWidget->setFixedWidth(45);

    // set scene
    auto scene = new MatrixScene;
    ui->graphicsView->setScene(scene);

    // set BG, FG color
    ui->BGColorPreview->setColor(MainWindow::BGColor);
    ui->FGColorPreview->setColor(MainWindow::FGColor);

    // set ColorPreview style
    ui->FGColorPreview->setStyleSheet("border: 3px solid black");
    ui->BGColorPreview->setStyleSheet("border: 3px inset grey");

	// set the id for the buttons in the buttonGroup
    ui->ToolbuttonGroup->setId(ui->pointerButton, Pointer);
    ui->ToolbuttonGroup->setId(ui->drawFreeButton, DrawFree);
    ui->ToolbuttonGroup->setId(ui->fillColorButton, FillColor);
    ui->ToolbuttonGroup->setId(ui->drawLineButton, DrawLine);
    ui->ToolbuttonGroup->setId(ui->drawRectButton, DrawRect);
    ui->ToolbuttonGroup->setId(ui->drawEllipseButton, DrawEllipse);
    ui->ToolbuttonGroup->setId(ui->drawTextButton, DrawTextbtn);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    auto about = new AboutDialog;
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

void MainWindow::setColor(QColor c)
{
    if (MainWindow::isFGSelected) {
        MainWindow::FGColor = c;
        ui->FGColorPreview->setColor(c);
    } else {
        MainWindow::BGColor = c;
        ui->BGColorPreview->setColor(c);
    }

}

void MainWindow::switchtoBG()
{
    MainWindow::isFGSelected = false;
    ui->BGColorPreview->setStyleSheet("border: 3px solid black");
    ui->FGColorPreview->setStyleSheet("border: 3px inset grey");
}

void MainWindow::switchtoFG()
{
    MainWindow::isFGSelected = true;
    ui->FGColorPreview->setStyleSheet("border: 3px solid black");
    ui->BGColorPreview->setStyleSheet("border: 3px inset grey");
}

void MainWindow::switchWindow()
{
    if(MainWindow::isPaintWindow){
        ui->windowButton->setIcon(QIcon(":/resources/icon/highlightPixel.svg"));
    }else{
        ui->windowButton->setIcon(QIcon(":/resources/icon/highlightWindow.svg"));
    }
    MainWindow::isPaintWindow = !MainWindow::isPaintWindow;
}

void MainWindow::setTool(int t)
{
    MainWindow::activeTool = static_cast<tool>(t);
    if(activeTool == Pointer){
        ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    }else{
        ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
    }
}
