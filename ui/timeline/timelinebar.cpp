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
	ui->setupUi(this);
	tlw = new TimeLineWidget();
	ui->scrollArea->setWidget(tlw);
	ui->scrollArea->setMinimumHeight(150);

	connect(ui->pushButton, SIGNAL(clicked(bool)), tlw, SLOT(addFrame()));
	connect(tlw, SIGNAL(durationChanged(QString)), ui->durationLable, SLOT(setText(QString)));
	connect(tlw, SIGNAL(setRange(int, int)), ui->horizontalSlider, SLOT(setRange(int, int)));
	connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->timeLable, SLOT(setNum(int)));
}

/**
 * @brief TimeLineBar::~TimeLineBar
 */

TimeLineBar::~TimeLineBar()
{
	delete tlw;
	delete ui;
}
