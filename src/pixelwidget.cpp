#include "pixelwidget.h"
#include "mainwindow.h"

#include <QPalette>
#include <QDebug>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>


PixelWidget::PixelWidget()
{
    // set black background
    setAutoFillBackground(true);
    highLigth(Qt::black);
    setMinimumSize(50, 50);
    setMaximumSize(50, 50);
}

void PixelWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    MainWindow::isMousePressed = true;
    if (MainWindow::isPaintWindow || MainWindow::activeTool == MainWindow::Pointer) {
        // pass event to pixelquartet to paint all pixels
        // or if activeTool is Pointer handle mouse drag
        event->ignore();

        return;
    } else if(MainWindow::activeTool == MainWindow::DrawFree){
        // set background color
        qDebug() << "pixel click";
        highLigth(event->buttons());
    }
}

void PixelWidget::highLigth(QColor c)
{
    // set background
    QPalette pal = palette();
    pal.setColor(QPalette::Background, c);
    setPalette(pal);
}

void PixelWidget::highLigth(Qt::MouseButtons btns)
{
    if (btns == Qt::LeftButton) {
        highLigth(MainWindow::FGColor);
    } else if(btns == Qt::RightButton){
        highLigth(MainWindow::BGColor);
    }
}
