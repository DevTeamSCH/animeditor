#include "timelinewidget.h"
#include "ui_timelinewidget.h"

#include <iostream>
#include <QTextStream>
/**
 * @brief TimeLineWidget::TimeLineWidget
 * @param parent
 */

TimeLineWidget::TimeLineWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::TimeLineWidget)
{
        layout->addStretch();
        this->setLayout(layout);
        ui->setupUi(this);

}

/**
 * @brief TimeLineWidget::~TimeLineWidget
 */

TimeLineWidget::~TimeLineWidget()
{
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != 0)  {
                delete child;
        }
        delete ui;
}

/**
 * @brief TimeLineWidget::addFrame
 * Insert FrameWidget the "at" or last ( if at ==0 ) place in the layout and set connection
 * @param fw    FrameWidget
 * @param at    int
 */

void TimeLineWidget::addFrame(FrameWidget *fw, int at)
{
        if(0 <= at && at < layout->count()){
                if (at != 0) {
                        layout->insertWidget(at, fw);
                } else {
                        layout->insertWidget(layout->count()-1, fw);
                }
                connect(fw, SIGNAL(selectedFrame(FrameWidget*)), this, SLOT(updateSelectedFrame(FrameWidget*)));
                connect(fw, SIGNAL(closeFrame(FrameWidget*)), this, SLOT(removeFrame(FrameWidget*)));
                connect(fw, SIGNAL(durationChanged(int)), this, SLOT(updateDuration(int)));
                updateSelectedFrame(fw);
                updateDuration(fw->getDuration());
        }
}

/**
 * @brief TimeLineWidget::updateSelectedFrame
 * @param fw
 */

void TimeLineWidget::updateSelectedFrame(FrameWidget * fw)
{
        if (selectedFrame != nullptr && selectedFrame != fw) {
                selectedFrame->unselectFrame();
        }
        selectedFrame = fw;
        selectedFrame->selectFrame();
        update();
}

/**
 * @brief TimeLineWidget::removeFrame
 * @param fw
 */

void TimeLineWidget::removeFrame(FrameWidget* fw)
{
        layout->removeWidget(fw);
        if (selectedFrame == fw) {
                selectedFrame = nullptr;
        }
        delete fw;
        fw = nullptr;
        update();
}

/**
 * @brief TimeLineWidget::updateDuration
 * @param change
 */

void TimeLineWidget::updateDuration(int change)
{
        duration += change;       
        emit durationChanged(milisecToTime(duration));
        emit setRange(0, duration);
}

QString TimeLineWidget::milisecToTime(int milisec)
{
        QString str;
        int min, sec, msec;
        msec = milisec;
        min = msec / 60000;
        msec -= min * 60000;
        sec = msec / 1000;
        msec -= sec * 1000;
        QTextStream strStream(&str);
        strStream<<min<<":"<<sec<<":"<<msec;
        return  str;
}
