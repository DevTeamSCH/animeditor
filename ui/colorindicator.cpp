#include "colorindicator.h"
#include "colorwheel.h"

#include <QPainter>

//Constructs a Color Indicator with the actual color black and before color white

ColorIndicator::ColorIndicator(QWidget *parent) :QWidget(parent)
{
        actual=QColor::fromRgb(0,0,0);
        before=QColor::fromRgb(255,255,255);
}

//Paints the indicator as two filled rectangles and the hex code of actual color

void ColorIndicator::paintEvent(QPaintEvent *ev){
        QPainter painter(this);
        painter.fillRect(QRect(0,0,50,20),QBrush(actual));
        painter.drawRect(QRect(0,0,50,20));
        painter.fillRect(QRect(60,0,50,20),QBrush(before));
        painter.drawRect(QRect(60,0,50,20));

        painter.drawText(QRect(0,30,100,30),"Selected: "+actual.name());
}

// Recommended size of the widget

QSize ColorIndicator::sizeHint()const{
        return QSize(120,120);
}

ColorIndicator::~ColorIndicator(){

}

//When the draw color changed the actual color becomes the new color,
//and the beofre become the actual

void ColorIndicator::updateColor(QColor color){
        if(actual.rgb()!=color.rgb()){
                before=actual;
                actual=color;
        }
        update();
}
