#ifndef PIXELGRAPHICSWIDGET_H
#define PIXELGRAPHICSWIDGET_H

#include <QGraphicsWidget>
#include <QColor>

class PixelWidget : public QGraphicsWidget
{
    Q_OBJECT
public:
    PixelWidget();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
public slots:
    void highLigth(QColor c = Qt::white);
};

#endif // PIXELGRAPHICSWIDGET_H
