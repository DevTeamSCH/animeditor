#ifndef BRUSHPROP_H
#define BRUSHPROP_H

#include <QWidget>
#include "property.h"
#include "../properties.h"

namespace Ui {
class BrushProp;
}

/*!
 * \brief The BrushProp class
 *
 * Property widget for brush tool
 */

class BrushProp : public Property
{
        Q_OBJECT

public:
        /*!
         * \brief BrushProp
         * \param parent
         * \param _prop
         *
         * Constructor
         */
        explicit BrushProp(QWidget *parent = 0,Properties *_prop=nullptr);
        ~BrushProp();

private slots:
        /*!
         * \brief on_spinBox_valueChanged
         * \param int arg1
         *
         * Sets the brush size when the spinbox value changes
         */
        void on_spinBox_valueChanged(int arg1);

private:
        Ui::BrushProp *ui;
};

#endif // BRUSHPROP_H
