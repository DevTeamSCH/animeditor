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
        /// Gets the brush size
        int getBrush();
        /// Gets the framerate
        int getFrameRate();
        /// Gets the frame size
        QSize getFrameSize();
        /// Gets the line size
        int getLine();

        /// Sets the brush size
        void setBrush(int);
        /// Gets the line size
        void setLine(int);

        explicit Properties(QWidget *parent = 0);
        ~Properties();

private slots:
        /// Wait for signal, when a tool changed
        void toolChanged(ToolState state);

        void getFrameSize(QSize);

private:
        /// Actually displayed poperty widget
        Property* actProp;
        Ui::Properties *ui;
};
#endif // PROPERTIES_H
