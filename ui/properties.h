#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QWidget>
#include "properties/property.h"
#include "properties/defprop.h"
#include "toolbar.h"

class Property;

namespace Ui {
class Properties;
}

/*!
 * \brief The Properties class
 *
 * Has the values of the properties, and fonction as
 * a container widget for the different property widgets.
 */

class Properties : public QWidget
{
        Q_OBJECT

        int frameRate=30;
        QSize frameSize;
        int brushSize=1;
        int lineSize=1;
        int textSize=5;
        //drawPrimitive
public:
        int getBrush();
        int getFrameRate();
        QSize getFrameSize();
        int getLine();

        void setBrush(int);
        void setLine(int);

        explicit Properties(QWidget *parent = 0);
        ~Properties();

private slots:

        void toolChanged(ToolState state);
        void getFrameSize(QSize);

private:
        Property* actProp;
        Ui::Properties *ui;
};
#endif // PROPERTIES_H
