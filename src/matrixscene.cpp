#include "matrixscene.h"
#include "mainwindow.h"
#include "pixelquartetwidget.h"
#include "pixelwidget.h"

#include <QGraphicsGridLayout>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsItem>

MatrixScene::MatrixScene(int x, int y)
{
    m_layout = new QGraphicsGridLayout;
    m_layout->setVerticalSpacing(100);
    m_layout->setHorizontalSpacing(20);
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++)
            m_layout->addItem(new PixelQuartetWidget, i, j);
    }
    auto form = new QGraphicsWidget;
    form->setLayout(m_layout);
    // set form background for testing
    form->setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::darkCyan);
    form->setPalette(pal);
    addItem(form);
}

void MatrixScene::toggleSpacing()
{
    if (m_has_spacing) {
        m_layout->setVerticalSpacing(0);
        m_layout->setHorizontalSpacing(0);
    } else {
        m_layout->setVerticalSpacing(100);
        m_layout->setHorizontalSpacing(20);
    }

    m_has_spacing = !m_has_spacing;
}

// handle mouse drag
void MatrixScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!items(event->scenePos()).isEmpty() && MainWindow::activeTool == MainWindow::DrawFree && MainWindow::isMousePressed){
        if(MainWindow::isPaintWindow && items(event->scenePos()).size() > 1){
            auto px = qgraphicsitem_cast<PixelQuartetWidget *>(items(event->scenePos())[1]);
            if(px) px->paintWindow(event->buttons());
        } else {
            auto px = qgraphicsitem_cast<PixelWidget *>(items(event->scenePos())[0]);
            if(px) px->highLigth(event->buttons());
        }
    } else{
        QGraphicsScene::mouseMoveEvent(event);
    }
}

void MatrixScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    MainWindow::isMousePressed = false;
    QGraphicsScene::mouseReleaseEvent(event);
}
