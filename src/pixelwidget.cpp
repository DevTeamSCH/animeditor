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
        event->ignore();

        return;
    } else {
        // set background color
        qDebug() << "pixel click";
        if (event->button() == Qt::LeftButton) {
            highLigth(MainWindow::FGColor);
        } else if(event->button() == Qt::RightButton) {
            highLigth(MainWindow::BGColor);
        }
    }
}

void PixelWidget::highLigth(QColor c)
{
    // set background
    QPalette pal = palette();
    pal.setColor(QPalette::Background, c);
    setPalette(pal);
}
