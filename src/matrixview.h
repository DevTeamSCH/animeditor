#ifndef MATRIXGRAPHICSVIEW_H
#define MATRIXGRAPHICSVIEW_H

#include <QGraphicsView>

class MatrixView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MatrixView(QWidget *parent = nullptr);

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
    void scaleView(qreal scaleFactor);
};

#endif // MATRIXGRAPHICSVIEW_H
