#ifndef DRAWPROP_H
#define DRAWPROP_H

#include <QWidget>
#include "property.h"

namespace Ui {
class DrawProp;
}

/*!
 * \brief The DrawProp class
 *
 * Property class for drawing primitives
 */

class DrawProp : public Property {
Q_OBJECT

public:
	/*!
	 * \brief DrawProp
	 * \param parent
	 * \param prop
	 *
	 * Construcor
	 */
	explicit DrawProp(QWidget *parent = 0, Properties *prop = nullptr);

	~DrawProp();

private:
	Ui::DrawProp *ui;
};

#endif // DRAWPROP_H
