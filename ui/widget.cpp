#include "widget.h"
#include "ui_widget.h"

PixelWidget::PixelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PixelWidget)
{
    ui->setupUi(this);
}

PixelWidget::PixelWidget(int size,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PixelWidget)
{
    squareSize=size;
    ui->setupUi(this);
}

PixelWidget::~PixelWidget()
{

    delete ui;
}

void PixelWidget::paintEvent(QPaintEvent *event){
       QPainter painter(this);
       this->setMinimumSize(15,15);
       this->setMaximumSize(15,15);
       painter.fillRect(event->rect(), QBrush(color));
}

void PixelWidget::mousePressEvent(QMouseEvent *event){
        if(event->button()==Qt::LeftButton)
            color=QColor(qrand()%256,qrand()%256,qrand()%256);
        update();
}

void PixelWidget::setSquareSize(int size){
    if(size>0)
    squareSize=size;
}
