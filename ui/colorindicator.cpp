#include "colorindicator.h"
#include "colorwheel.h"

#include <QPainter>

ColorIndicator::ColorIndicator(QWidget *parent) :QWidget(parent)
{
        actual=QColor::fromRgb(0,0,0);
        before=QColor::fromRgb(255,255,255);
}

void ColorIndicator::paintEvent(QPaintEvent *ev){
        QPainter painter(this);
        painter.fillRect(QRect(0,0,50,20),QBrush(actual));
        painter.drawRect(QRect(0,0,50,20));
        painter.fillRect(QRect(60,0,50,20),QBrush(before));
        painter.drawRect(QRect(60,0,50,20));

        painter.drawText(QRect(0,30,100,30),"Selected: "+actual.name());
}

QSize ColorIndicator::sizeHint()const{
        return QSize(120,120);
}

ColorIndicator::~ColorIndicator(){

}

void ColorIndicator::updateColor(QColor color){
        if(actual.rgb()!=color.rgb()){
                before=actual;
                actual=color;
        }
        update();
}
