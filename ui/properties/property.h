#ifndef PROPERTY_H
#define PROPERTY_H

#include <QWidget>

namespace Ui {
class Property;
}

class Property : public QWidget
{
        Q_OBJECT

public:
        explicit Property(QWidget *parent = 0);
        ~Property();

private:
        Ui::Property *ui;
};

#endif // PROPERTY_H
