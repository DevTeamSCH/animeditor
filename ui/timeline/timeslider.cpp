#include "timeslider.h"
#include "ui_timeslider.h"

TimeSlider::TimeSlider(QWidget *parent) :
    QSlider(parent),
    ui(new Ui::TimeSlider)
{
    ui->setupUi(this);
    init();
}

TimeSlider::~TimeSlider()
{
    delete ui;    
}

void TimeSlider::init()
{
    setOrientation(Qt::Horizontal);
}
