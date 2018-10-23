#ifndef MATRIXGRAPHICSSCENE_H
#define MATRIXGRAPHICSSCENE_H

#include <QGraphicsScene>

class MatrixScene : public QGraphicsScene
{
public:
    MatrixScene(int x = 13, int y = 16);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MATRIXGRAPHICSSCENE_H
