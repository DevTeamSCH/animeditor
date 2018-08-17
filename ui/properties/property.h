#ifndef PROPERTY_H
#define PROPERTY_H

#include <QWidget>

class Properties;

namespace Ui {
class Property;
}

class Property : public QWidget
{
        Q_OBJECT

public:
        explicit Property(QWidget *parent = 0,Properties* p=nullptr);
        ~Property();
protected:
         Properties* prop;

private:
        Ui::Property *ui;
};

#endif // PROPERTY_H
