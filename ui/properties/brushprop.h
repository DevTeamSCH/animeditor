#ifndef BRUSHPROP_H
#define BRUSHPROP_H

#include <QWidget>
#include "property.h"

namespace Ui {
class BrushProp;
}

class BrushProp : public Property
{
        Q_OBJECT

public:
        explicit BrushProp(QWidget *parent = 0);
        ~BrushProp();

private:
        Ui::BrushProp *ui;
};

#endif // BRUSHPROP_H
