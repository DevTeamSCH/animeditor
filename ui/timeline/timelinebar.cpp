#include "timelinebar.h"
#include "ui_timelinebar.h"
#include <iostream>

/**
 * @brief TimeLineBar::TimeLineBar
 * @param parent
 */

TimeLineBar::TimeLineBar(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::TimeLineBar)
{
    init();

//	connect(ui->pushButton, SIGNAL(clicked(bool)), tlw, SLOT(addFrame()));
//	connect(tlw, SIGNAL(durationChanged(QString)), ui->durationLable, SLOT(setText(QString)));
//    connect(tlw, SIGNAL(setRange(int, int)), ui->horizontalSlider, SLOT(setRange(int, int)));
//	connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->timeLable, SLOT(setNum(int)));
}

/**
 * @brief TimeLineBar::~TimeLineBar
 */

TimeLineBar::~TimeLineBar()
{
    delete actualTime;
    delete durationTime;
    delete separator;
    delete timeSlider;
    delete nextButton;
    delete previousButton;
    delete startStopButton;
	delete ui;
}

void TimeLineBar::init()
{
    ui->setupUi(this);

    actualTime = new TimeLabel();
    durationTime = new TimeLabel();
    separator = new QLabel("/");
    timeSlider = new TimeSlider();
    nextButton = new QPushButton();
    previousButton = new QPushButton();
    startStopButton = new StartStopButton();

    ui->timeLabelsAndTimeSlider->addWidget(actualTime);
    ui->timeLabelsAndTimeSlider->addWidget(separator);
    ui->timeLabelsAndTimeSlider->addWidget(durationTime);
    ui->timeLabelsAndTimeSlider->addWidget(timeSlider);
    ui->timeLabelsAndTimeSlider->addWidget(previousButton);
    ui->timeLabelsAndTimeSlider->addWidget(startStopButton);
    ui->timeLabelsAndTimeSlider->addWidget(nextButton);


    ui->scrollArea->setMinimumHeight(150);
}
