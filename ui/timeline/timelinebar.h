#ifndef TIMELINEBAR_H
#define TIMELINEBAR_H

#include <QWidget>
#include "timelinewidget.h"

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
	TimeLineWidget *tlw;

};

#endif // TIMELINEBAR_H
