#ifndef PROPERTY_H
#define PROPERTY_H

#include <QWidget>

class Properties;

namespace Ui {
class Property;
}

/*!
 * \brief The Property class
 *
 * Property base class for the special property classes
 * Instance this isn't recommended, instead inherit this.
 */

class Property : public QWidget {
Q_OBJECT

public:
	/*!
	 * \brief Property
	 * \param parent
	 * \param p
	 *
	 * Constructor, connect the Properties ("model") to property classes
	 */
	explicit Property(QWidget *parent = 0, Properties *p = nullptr);

	~Property();

protected:
	/// Pointer to the Properties ("model"), which holds the values of properties
	Properties *prop;

private:
	Ui::Property *ui;
};

#endif // PROPERTY_H
