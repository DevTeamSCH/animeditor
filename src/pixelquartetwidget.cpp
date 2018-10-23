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
    layout->setVerticalSpacing(0); layout->setHorizontalSpacing(0);
    auto px1 = new PixelWidget;
    auto px2 = new PixelWidget;
    auto px3 = new PixelWidget;
    auto px4 = new PixelWidget;

    // arrange items
    layout->addItem(px1, 0, 0);
    layout->addItem(px2, 0, 1);
    layout->addItem(px3, 1, 0);
    layout->addItem(px4, 1, 1);
    setLayout(layout);

    // connect pixels with quartet
    connect(this, &PixelQuartetWidget::clicked, px1, &PixelWidget::highLigth);
    connect(this, &PixelQuartetWidget::clicked, px2, &PixelWidget::highLigth);
    connect(this, &PixelQuartetWidget::clicked, px3, &PixelWidget::highLigth);
    connect(this, &PixelQuartetWidget::clicked, px4, &PixelWidget::highLigth);
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
