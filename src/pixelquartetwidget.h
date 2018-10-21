#ifndef PIXELQUARTETGRAPHICSWIDGET_H
#define PIXELQUARTETGRAPHICSWIDGET_H

#include <QGraphicsWidget>
#include <QColor>

class PixelQuartetWidget : public QGraphicsWidget
{
    Q_OBJECT
public:
    PixelQuartetWidget();
signals:
    void clicked(QColor c = Qt::white);

    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PIXELQUARTETGRAPHICSWIDGET_H
