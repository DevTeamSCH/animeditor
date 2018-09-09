#ifndef DEFPROP_H
#define DEFPROP_H

#include <QWidget>
#include "property.h"
#include "../properties.h"

namespace Ui {
class DefProp;
}
/*!
 * \brief The DefProp class
 *
 * Default property widget.
 */

class DefProp : public Property
{
        Q_OBJECT

public:
        /*!
         * \brief DefProp
         * \param parent
         * \param prop
         *
         * Constructor
         */
        explicit DefProp(QWidget *parent = 0,Properties *prop=nullptr);
        ~DefProp();

private:
        Ui::DefProp *ui;
};

#endif // DEFPROP_H
