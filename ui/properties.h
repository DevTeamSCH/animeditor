#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QWidget>
#include "properties/property.h"
#include "properties/defprop.h"
#include "properties/drawprop.h"
#include "properties/brushprop.h"
#include "toolbar.h"

class Property;

namespace Ui {
class Properties;
}

class Properties : public QWidget
{
        Q_OBJECT

        int frameRate;
        int frameSize;
        int brushSize=1;
        int lineSize;
        int textSize;
        //drawPrimitive
public:
        int getBrush();
        void setBrush(int);

        int getFrameRate();
        int getFrameSize();
        int getLine();
        void setLine(int);

        explicit Properties(QWidget *parent = 0);
        ~Properties();

private slots:

        void toolChanged(ToolState state);

private:
        Property* actProp=new DefProp(this);
        //ProertyModel* prop;
        Ui::Properties *ui;
};
/*
class PropertyModel{
        int frameRate;
        int frameSize;
        int brushSize;
        int lineSize;
        int textSize;
        //drawPrimitive
public:
        int getBrush();
        void setBrush(int);

        int getFrameRate();
        int getFrameSize();
        int getLine();
        void setLine(int);

        int getLine();
        void setLine(int);
}
*/
#endif // PROPERTIES_H
