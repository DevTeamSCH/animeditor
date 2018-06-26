#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QColor>


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
        virtual QSize sizeHint() const override;
        virtual QSize minimumSizeHint() const override;

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
