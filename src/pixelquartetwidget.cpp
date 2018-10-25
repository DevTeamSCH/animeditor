#include "pixelquartetwidget.h"
#include "pixelwidget.h"
#include "mainwindow.h"

#include <QGraphicsGridLayout>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

PixelQuartetWidget::PixelQuartetWidget()
{
    // set background for testing
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::darkMagenta);
    setAutoFillBackground(true);
    setPalette(pal);

    // set grid layout
    auto layout = new QGraphicsGridLayout();
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    for (int i=0; i <= 1; i++) {
        for (int j=0; j <= 1; j++) {
            auto pixel = new PixelWidget;
            layout->addItem(pixel, i, j);
            connect(this, &PixelQuartetWidget::clicked, pixel, &PixelWidget::highLigth);
        }
    }
    setLayout(layout);
}

void PixelQuartetWidget::paintWindow(bool leftClick)
{
    if (MainWindow::isPaintWindow && MainWindow::activeTool != MainWindow::Pointer) {
        if (leftClick) {
            emit clicked(MainWindow::FGColor);
        } else {
            emit clicked(MainWindow::BGColor);
        }
    }
}


void PixelQuartetWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "quartet click";
    paintWindow(event->button() == Qt::LeftButton);
    event->ignore(); return;
}
