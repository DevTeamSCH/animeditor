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
            connect(this, SIGNAL(clicked(Qt::MouseButtons)), pixel, SLOT(highLigth(Qt::MouseButtons)));
        }
    }
    setLayout(layout);
}

void PixelQuartetWidget::paintWindow(Qt::MouseButtons btns)
{
    if (MainWindow::isPaintWindow && MainWindow::activeTool == MainWindow::DrawFree) {
        emit clicked(btns);
    }
}


void PixelQuartetWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "quartet click";
    paintWindow(event->button());
    event->ignore(); return;
}
