#include "colorindicator.h"
#include "colorwheel.h"

#include <QPainter>
#include <QMouseEvent>

//Constructs a Color Indicator with the actual color black and before color white

ColorIndicator::ColorIndicator(QWidget *parent) :QWidget(parent)
{
        actual=QColor::fromRgb(0,0,0);
        before=QColor::fromRgb(255,255,255);
}

//Paints the indicator as two filled rectangles and the hex code of actual color

void ColorIndicator::paintEvent(QPaintEvent *ev){
        QPainter painter(this);
        painter.fillRect(QRect(this->size().width()/2-55,0,50,20),QBrush(actual));
        painter.drawRect(QRect(this->size().width()/2-55,0,50,20));
        painter.fillRect(QRect(this->size().width()/2+5,0,50,20),QBrush(before));
        painter.drawRect(QRect(this->size().width()/2+5,0,50,20));

}

// If the user clicks on the 2nd rect the colors swap

void ColorIndicator::mousePressEvent(QMouseEvent* event){
        if(event->button()==Qt::LeftButton){
                if(event->localPos().x()>=this->size().width()/2+5 && event->localPos().x()<=this->size().width()/2+5+50 &&
                   event->localPos().y()>=0 && event->localPos().y()<=20 )
                        emit colorChanged(before);
        }

}

// Recommended size of the widget

QSize ColorIndicator::sizeHint()const{
        return QSize(120,50);
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
