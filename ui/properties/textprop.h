#ifndef TEXTPROP_H
#define TEXTPROP_H

#include <QWidget>
#include "property.h"

namespace Ui {
class TextProp;
}

class TextProp : public Property
{
        Q_OBJECT

public:
        explicit TextProp(QWidget *parent = 0);
        ~TextProp();

private:
        Ui::TextProp *ui;
};

#endif // TEXTPROP_H
