#include "framewidget.h"
#include "ui_framewidget.h"
#include <iostream>

FrameWidget::FrameWidget(QString name, unsigned int duration, QWidget *parent) :
    name(name),
    duration(duration),
    QWidget(parent),
    ui(new Ui::FrameWidget)
{
        ui->setupUi(this);
        init();
}

FrameWidget::~FrameWidget()
{
        delete ui;
}

QSize FrameWidget::sizeHint() const{
    return QSize(width, height);
}

QSize FrameWidget::minimumSizeHint() const{
    return QSize(width, height);
}

void FrameWidget::init(){
    connect(ui->name, SIGNAL(textChanged(QString)), this, SLOT(updateName(QString)));
    connect(ui->duration, SIGNAL(valueChanged(int)), this, SLOT(updateDuration(int)));
    connect(ui->close, SIGNAL(clicked(bool)), this, SLOT(Close()));
}

void FrameWidget::updateName(QString name){
    this->name = name;
}

void FrameWidget::updateDuration(int duration){
    emit durationChanged(duration - this->duration);
    this->duration = duration;
}

void FrameWidget::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
            emit selectedFrame(this);
    }
    update();
}

void FrameWidget::setColor(QColor color){
    QPalette pal = palette();
    pal.setColor(QPalette::Background, color);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->show();
}

void FrameWidget::selectFrame(){
    setColor(selectedColor);
}

void FrameWidget::unselectFrame(){
    setColor(unselectedColor);
}

void FrameWidget::Close(){
    emit durationChanged((-1) * duration);
    emit closeFrame(this);
}

int FrameWidget::getDuration(){
    return duration;
}
