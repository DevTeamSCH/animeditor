#ifndef PIXELGRAPHICSWIDGET_H
#define PIXELGRAPHICSWIDGET_H

#include <QGraphicsWidget>
#include <QColor>

class PixelWidget : public QGraphicsWidget
{
    Q_OBJECT
public:
    enum { Type = UserType + 1 };

    int type() const override
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }
    PixelWidget();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

public slots:
    void highLigth(QColor c = Qt::white);
};

#endif // PIXELGRAPHICSWIDGET_H
