#ifndef MATRIXGRAPHICSSCENE_H
#define MATRIXGRAPHICSSCENE_H

#include <QGraphicsScene>

class QGraphicsGridLayout;

class MatrixScene : public QGraphicsScene
{
public:
    MatrixScene(int x = 13, int y = 16);
    void toggleSpacing();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QGraphicsGridLayout* m_layout;
    bool m_has_spacing = true;
};

#endif // MATRIXGRAPHICSSCENE_H
