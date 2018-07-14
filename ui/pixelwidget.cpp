#include "pixelwidget.h"
#include "ui_widget.h"
#include "pixelframe.h"
#include "frameelement.h"

PixelWidget::PixelWidget(QWidget *parent,unsigned p) :QWidget(parent),ui(new Ui::PixelWidget),pos(p)
{
        ui->setupUi(this);
}

PixelWidget::PixelWidget(int size,QWidget *parent) :QWidget(parent), ui(new Ui::PixelWidget)
{
        squareSize=size;
        ui->setupUi(this);
}

PixelWidget::~PixelWidget()
{
         delete ui;
}

void PixelWidget::paintEvent(QPaintEvent *event)
{
        QPainter painter(this);
        painter.fillRect(event->rect(), QBrush(color));
}

QSize PixelWidget::sizeHint() const{
        return QSize(12,12);
}

QSize PixelWidget::minimumSizeHint() const{
        return QSize(10,10);
}

void PixelWidget::mousePressEvent(QMouseEvent *event)
{
        if(event->button()==Qt::LeftButton){
                color=((FrameElement*)parent())->getColor();
        }
        update();
}

void PixelWidget::mouseMoveEvent(QMouseEvent *event)
{

        update();
}

void PixelWidget::setSquareSize(int size){
        if(size>0)
        squareSize=size;
}

void PixelWidget::setPos(unsigned p){
        pos=p;
}
unsigned PixelWidget::getPos(){
        return pos;
}
