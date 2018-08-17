#ifndef BRUSHPROP_H
#define BRUSHPROP_H

#include <QWidget>
#include "property.h"
#include "../properties.h"

namespace Ui {
class BrushProp;
}

class BrushProp : public Property
{
        Q_OBJECT

public:
        explicit BrushProp(QWidget *parent = 0,Properties *prop=nullptr);
        ~BrushProp();

private:
        Ui::BrushProp *ui;
};

#endif // BRUSHPROP_H
