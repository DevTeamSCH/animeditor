#ifndef LINEPROP_H
#define LINEPROP_H

#include <QWidget>
#include <QWidget>
#include "property.h"
#include "../properties.h"

namespace Ui {
class LineProp;
}

class LineProp : public Property
{
        Q_OBJECT

public:
        explicit LineProp(QWidget *parent = 0,Properties *_prop=nullptr);
        ~LineProp();

private slots:
        void on_spinBox_valueChanged(int arg1);

private:
        Ui::LineProp *ui;
};
#endif // LINEPROP_H
