#ifndef FRAMEWIDGET_H
#define FRAMEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QColor>

namespace Ui {
class frameWidget;
}

class frameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit frameWidget(QWidget *parent = 0);
    explicit frameWidget(int x, int y, int width, int height, QWidget *parent = 0);
    ~frameWidget();

protected:
        void paintEvent(QPaintEvent *event) override;
private:
    Ui::frameWidget *ui;
    int x, y, width, height;
    QColor color = QColor(0,0,0);
};

#endif // FRAMEWIDGET_H
