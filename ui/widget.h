#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QColor>
#include "widget.h"


namespace Ui {
class PixelWidget;
}

class PixelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PixelWidget(QWidget *parent = 0);
    PixelWidget(int size,QWidget *parent=0);
    ~PixelWidget();
    void setSquareSize(int size);

public slots:



signals:

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::PixelWidget *ui;

    QColor color=QColor(255,0,0);
    int squareSize=20;

};

#endif // WIDGET_H
