#include "pixelquartetwidget.h"
#include "pixelwidget.h"

#include <QGraphicsGridLayout>
#include <QtDebug>

PixelQuartetWidget::PixelQuartetWidget()
{
    // set black background
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::darkMagenta);
    setAutoFillBackground(true);
    setPalette(pal);

    // set layout
    QGraphicsGridLayout *layout = new QGraphicsGridLayout();
    layout->setVerticalSpacing(0); layout->setHorizontalSpacing(0);
    auto px1 = new PixelWidget;
    auto px2 = new PixelWidget;
    auto px3 = new PixelWidget;
    auto px4 = new PixelWidget;

    layout->addItem(px1, 0, 0);
    layout->addItem(px2, 0, 1);
    layout->addItem(px3, 1, 0);
    layout->addItem(px4, 1, 1);
    setLayout(layout);

    // connect pixel whith quartet
    connect(this, &PixelQuartetWidget::clicked, px1, &PixelWidget::highLigth);
    connect(this, &PixelQuartetWidget::clicked, px2, &PixelWidget::highLigth);
    connect(this, &PixelQuartetWidget::clicked, px3, &PixelWidget::highLigth);
    connect(this, &PixelQuartetWidget::clicked, px4, &PixelWidget::highLigth);
}


void PixelQuartetWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(Qt::blue);
}
