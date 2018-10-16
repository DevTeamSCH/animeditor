#ifndef TIMELINEBAR_H
#define TIMELINEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "startstopbutton.h"
#include "timelinewidget.h"
#include "timelabel.h"
#include "timeslider.h"

namespace Ui {
class TimeLineBar;
}

class TimeLineBar : public QWidget {
Q_OBJECT

public:
	explicit TimeLineBar(QWidget *parent = 0);

	~TimeLineBar();

private:
    Ui::TimeLineBar *ui;

    TimeLabel *actualTime;
    TimeLabel *durationTime;
    QLabel *separator;
    TimeSlider *timeSlider;
    QPushButton *nextButton;
    QPushButton *previousButton;
    StartStopButton *startStopButton;
    void init();

};

#endif // TIMELINEBAR_H
