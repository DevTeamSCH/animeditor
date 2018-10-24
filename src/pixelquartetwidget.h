#ifndef PIXELQUARTETGRAPHICSWIDGET_H
#define PIXELQUARTETGRAPHICSWIDGET_H

#include <QGraphicsWidget>
#include <QColor>

class PixelQuartetWidget : public QGraphicsWidget
{
    Q_OBJECT
public:
    enum { Type = UserType + 2 };

    int type() const override
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }
    PixelQuartetWidget();

public slots:
    void paintWindow(bool leftClick);

signals:
    void clicked(QColor c = Qt::white);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // PIXELQUARTETGRAPHICSWIDGET_H
