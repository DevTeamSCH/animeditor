#include "framewidget.h"
#include "ui_framewidget.h"
#include <iostream>

/**
 * @brief FrameWidget::FrameWidget
 * @param name
 * @param duration
 * @param parent
 */

FrameWidget::FrameWidget(QString name, unsigned int duration, QWidget *parent) :
	name(name),
	duration(duration),
	QWidget(parent),
	ui(new Ui::FrameWidget)
{
	ui->setupUi(this);
	init();
}

/**
 * @brief FrameWidget::~FrameWidget
 */

FrameWidget::~FrameWidget()
{
	delete ui;
}

/**
 * @brief FrameWidget::sizeHint
 * @return
 */

QSize FrameWidget::sizeHint() const
{
	return QSize(width, height);
}

/**
 * @brief FrameWidget::minimumSizeHint
 * @return
 */

QSize FrameWidget::minimumSizeHint() const
{
	return QSize(width, height);
}

/**
 * @brief FrameWidget::init
 */

/**
 * @brief FrameWidget::init
 */

void FrameWidget::init()
{
	connect(ui->name, SIGNAL(textChanged(QString)), this, SLOT(updateName(QString)));
	connect(ui->duration, SIGNAL(valueChanged(int)), this, SLOT(updateDuration(int)));
	connect(ui->close, SIGNAL(clicked(bool)), this, SLOT(Close()));
}

/**
 * @brief FrameWidget::updateName
 * @param name
 */

void FrameWidget::updateName(QString name)
{
	this->name = name;
}

/**
 * @brief FrameWidget::updateDuration
 * @param duration
 */

void FrameWidget::updateDuration(int duration)
{
	emit durationChanged(duration - this->duration);
	this->duration = duration;
}

/**
 * @brief FrameWidget::mousePressEvent
 * @param event
 */

void FrameWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		emit selectedFrame(this);
	}
	update();
}

/**
 * @brief FrameWidget::setColor
 * @param color
 */

void FrameWidget::setColor(QColor color)
{
	QPalette pal = palette();
	pal.setColor(QPalette::Background, color);
	this->setAutoFillBackground(true);
	this->setPalette(pal);
	this->show();
}

/**
 * @brief FrameWidget::selectFrame
 */

void FrameWidget::selectFrame()
{
	setColor(selectedColor);
}

/**
 * @brief FrameWidget::unselectFrame
 */

void FrameWidget::unselectFrame()
{
	setColor(unselectedColor);
}

/**
 * @brief FrameWidget::Close
 */

void FrameWidget::Close()
{
	emit durationChanged((-1) * duration);
	emit closeFrame(this);
}

/**
 * @brief FrameWidget::getDuration
 * @return
 */

int FrameWidget::getDuration()
{
	return duration;
}
