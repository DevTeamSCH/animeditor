#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QWidget>
#include "properties/property.h"
#include "properties/defprop.h"
#include "properties/drawprop.h"
#include "properties/brushprop.h"
#include "toolbar.h"

namespace Ui {
class Properties;
}

class Properties : public QWidget
{
        Q_OBJECT

public:
        explicit Properties(QWidget *parent = 0);
        ~Properties();

private slots:

        void toolChanged(ToolState state);
        void on_pushButton_clicked();

private:
        Property* actProp=new DefProp();
        Ui::Properties *ui;
};

#endif // PROPERTIES_H
