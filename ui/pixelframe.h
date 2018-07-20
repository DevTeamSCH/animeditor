#ifndef PIXELFRAME_H
#define PIXELFRAME_H

#include <QWidget>

namespace Ui {
class PixelFrame;
}

class PixelFrame : public QWidget
{
        Q_OBJECT

public:

        explicit PixelFrame(unsigned sizeX, unsigned sizeY, QWidget *parent=0);
        ~PixelFrame();
        QColor getDrawColor();
        QSize sizeHint() const override;

//        QSize minimumSizeHint() const override;

private:
        Ui::PixelFrame *ui;
        unsigned x,y;
        QColor drawColor;

public slots:
        void updateColor(QColor);
};

#endif // PIXELFRAME_H
