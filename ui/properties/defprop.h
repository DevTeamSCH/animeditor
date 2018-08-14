#ifndef DEFPROP_H
#define DEFPROP_H

#include <QWidget>
#include "property.h"

namespace Ui {
class DefProp;
}

class DefProp : public Property
{
        Q_OBJECT

public:
        explicit DefProp(QWidget *parent = 0);
        ~DefProp();

private:
        Ui::DefProp *ui;
};

#endif // DEFPROP_H
