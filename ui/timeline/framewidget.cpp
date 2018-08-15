#include "framewidget.h"
#include "ui_framewidget.h"

frameWidget::frameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frameWidget)
{
        ui->setupUi(this);
}

frameWidget::frameWidget(int x, int y, int width, int height, QWidget *parent) :
    x(x), y(y), height(height), width(width),
    QWidget(parent),
    ui(new Ui::frameWidget)
{
        ui->setupUi(this);
}

frameWidget::~frameWidget()
{
        delete ui;
}


void frameWidget::paintEvent(QPaintEvent *event){
         QPainter painter(this);
         painter.fillRect(x, y, x+width, y+height, color);
}
