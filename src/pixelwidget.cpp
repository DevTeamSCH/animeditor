#include "pixelwidget.h"
#include <QPalette>
#include <QDebug>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>

PixelWidget::PixelWidget()
{
    // set black background
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(pal);
}


void PixelWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (true) {
        event->ignore();
    } else {
        // set black background
        QPalette pal = palette();
        pal.setColor(QPalette::Background, Qt::red);
        setPalette(pal);
    }
}

void PixelWidget::highLigth(QColor c)
{
    // set black background
    QPalette pal = palette();
    pal.setColor(QPalette::Background, c);
    setAutoFillBackground(true);
    setPalette(pal);
}
