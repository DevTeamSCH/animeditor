#ifndef FRAMEELEMENT_H
#define FRAMEELEMENT_H

#include <QWidget>
#include "pixelwidget.h"

namespace Ui {
class FrameElement;
}

class FrameElement : public QWidget
{
        Q_OBJECT

public:
        explicit FrameElement(QWidget *parent = 0);
        ~FrameElement();

        virtual QSize sizeHint() const override;
        virtual QSize minimumSizeHint() const override;

private:
        QVector<PixelWidget*> pixels;
        Ui::FrameElement *ui;

};
#endif // FRAMEELEMENT_H
