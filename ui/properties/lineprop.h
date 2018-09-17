#ifndef LINEPROP_H
#define LINEPROP_H

#include <QWidget>
#include <QWidget>
#include "property.h"
#include "../properties.h"

namespace Ui {
class LineProp;
}

/*!
 * \brief The LineProp class
 *
 * Poperty class for line tool
 */

class LineProp : public Property {
Q_OBJECT

public:
	/*!
	 * \brief LineProp
	 * \param parent
	 * \param _prop
	 *
	 * Constructor
	 */
	explicit LineProp(QWidget *parent = 0, Properties *_prop = nullptr);

	~LineProp();

private slots:

	/*!
	 * \brief on_spinBox_valueChanged
	 * \param arg1
	 *
	 * Sets the line size when the spinbox value changes
	 */
	void on_spinBox_valueChanged(int arg1);

private:
	Ui::LineProp *ui;
};

#endif // LINEPROP_H
