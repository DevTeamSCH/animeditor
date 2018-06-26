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

private:
        Ui::PixelFrame *ui;
};

#endif // PIXELFRAME_H
