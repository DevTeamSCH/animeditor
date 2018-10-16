#include "timelabel.h"
#include "ui_timelabel.h"

#include <qtextstream.h>



TimeLabel::TimeLabel(QWidget *parent) :
    QLabel (parent),
    ui(new Ui::TimeLabel)
{
    ui->setupUi(this);
    init();
}

TimeLabel::~TimeLabel()
{
    delete ui;
}

void TimeLabel::milisecToTime(int milisec)
{
    QString str;
    int min, sec, msec;
    msec = milisec;
    min = msec / 60000;
    msec -= min * 60000;
    sec = msec / 1000;
    msec -= sec * 1000;
    QTextStream strStream(&str);
    strStream << min << ":" << sec << ":" << msec;
    setText(str);
}


void TimeLabel::init()
{
    setText(startText);
}
