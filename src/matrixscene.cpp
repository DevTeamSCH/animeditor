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
    // connect(MainWindow::toggleSpacing, &QPushButton::clicked, this, &MatrixScene::toggleSpacing);
    m_layout = new QGraphicsGridLayout;
    m_layout->setVerticalSpacing(100);
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++)
            m_layout->addItem(new PixelQuartetWidget, i, j);
    }
    auto form = new QGraphicsWidget;
    form->setLayout(m_layout);
    addItem(form);
}

void MatrixScene::toggleSpacing()
{
    if (m_has_spacing) {
        m_layout->setVerticalSpacing(0);
    } else {
        m_layout->setVerticalSpacing(100);
    }

    m_has_spacing = !m_has_spacing;
}

// handle mouse drag
void MatrixScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!items(event->scenePos()).isEmpty() && MainWindow::activeTool != MainWindow::Pointer && MainWindow::isMousePressed){
        if(MainWindow::isPaintWindow && items(event->scenePos()).size() > 1){
            auto px = qgraphicsitem_cast<PixelQuartetWidget *>(items(event->scenePos())[1]);
            if(px) px->paintWindow(event->buttons() == Qt::LeftButton);
        } else {
            auto px = qgraphicsitem_cast<PixelWidget *>(items(event->scenePos())[0]);
            if(px){
                if (event->buttons() == Qt::LeftButton) {
                    px->highLigth(MainWindow::FGColor);
                } else if(event->buttons() == Qt::RightButton) {
                    px->highLigth(MainWindow::BGColor);
                }
            }
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
