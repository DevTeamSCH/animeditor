#ifndef TEXTPROP_H
#define TEXTPROP_H

#include <QWidget>
#include "property.h"

namespace Ui {
class TextProp;
}

/*!
 * \brief The TextProp class
 *
 *Property class for texts
 */

class TextProp : public Property {
Q_OBJECT

public:
	/*!
	 * \brief TextProp
	 * \param parent
	 * \param prop
	 *
	 * Constructor
	 */
	explicit TextProp(QWidget *parent = 0, Properties *prop = nullptr);

	~TextProp();

private:
	Ui::TextProp *ui;
};

#endif // TEXTPROP_H
