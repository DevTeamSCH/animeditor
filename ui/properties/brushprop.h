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
        explicit BrushProp(QWidget *parent = 0,Properties *_prop=nullptr);
        ~BrushProp();

private slots:
        void on_spinBox_valueChanged(int arg1);

private:
        Ui::BrushProp *ui;
};

#endif // BRUSHPROP_H
