#include "matrixscene.h"

#include "pixelquartetwidget.h"
#include <QGraphicsGridLayout>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

MatrixScene::MatrixScene(int x, int y)
{
    auto layout = new QGraphicsGridLayout;
    layout->setVerticalSpacing(100);
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++)
            layout->addItem(new PixelQuartetWidget, i, j);
    }
    auto form = new QGraphicsWidget;
    form->setLayout(layout);
    addItem(form);
}
