#ifndef DRAWPROP_H
#define DRAWPROP_H

#include <QWidget>
#include "property.h"

namespace Ui {
class DrawProp;
}

class DrawProp : public Property
{
        Q_OBJECT

public:
        explicit DrawProp(QWidget *parent = 0);
        ~DrawProp();

private:
        Ui::DrawProp *ui;
};

#endif // DRAWPROP_H
