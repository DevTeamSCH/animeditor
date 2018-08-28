#include "timelinebar.h"
#include "ui_timelinebar.h"


TimeLineBar::TimeLineBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeLineBar)
{
    ui->setupUi(this);
    tlw = new TimeLineWidget();
    ui->scrollArea->setWidget(tlw);
    ui->scrollArea->setMinimumHeight(150);

    connect(ui->pushButton, SIGNAL(clicked(bool)), tlw, SLOT(addFrame()));
    connect(tlw, SIGNAL(durationChanged(int)), ui->durationLable, SLOT(setNum(int)));
    connect(tlw, SIGNAL(setRange(int,int)), ui->horizontalSlider, SLOT(setRange(int,int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->time, SLOT(setNum(int)));
}

TimeLineBar::~TimeLineBar()
{
    delete tlw;
    delete ui;
}
