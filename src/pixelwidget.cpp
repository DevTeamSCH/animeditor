#include "pixelwidget.h"
#include "mainwindow.h"

#include <QPalette>
#include <QDebug>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>


PixelWidget::PixelWidget()
{
    // set black background
    setAcceptHoverEvents(true);
    setAutoFillBackground(true);
    highLigth(Qt::black);
}

void PixelWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (MainWindow::isPaintWindow) {
        // pass event to pixelquartet to paint all pixels
        event->ignore();
    } else {
        // set background color
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
