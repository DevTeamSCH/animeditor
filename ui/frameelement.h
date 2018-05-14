#ifndef FRAMEELEMENT_H
#define FRAMEELEMENT_H

#include <QWidget>
#include "widget.h"

namespace Ui {
class FrameElement;
}

class FrameElement : public QWidget
{
    Q_OBJECT

public:
    explicit FrameElement(QWidget *parent = 0);
    ~FrameElement();
    void resizeEvent(QResizeEvent *event) override;

private:
    QVector<PixelWidget*> pixels;
    Ui::FrameElement *ui;

};

#endif // FRAMEELEMENT_H
