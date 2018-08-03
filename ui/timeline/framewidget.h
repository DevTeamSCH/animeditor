#ifndef FRAMEWIDGET_H
#define FRAMEWIDGET_H

#include <QWidget>

namespace Ui {
class frameWidget;
}

class frameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit frameWidget(QWidget *parent = 0);
    ~frameWidget();

private:
    Ui::frameWidget *ui;
};

#endif // FRAMEWIDGET_H
