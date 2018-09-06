#include "timelinewidget.h"
#include "ui_timelinewidget.h"

#include <iostream>

TimeLineWidget::TimeLineWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::TimeLineWidget)
{
        layout->addStretch();
        //addFrame(new FrameWidget("alma", 1000));

        this->setLayout(layout);
        ui->setupUi(this);

}

TimeLineWidget::~TimeLineWidget()
{
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != 0)  {
                delete child;
        }
        delete ui;
}

void TimeLineWidget::addFrame(FrameWidget *fw, int at){
        if(0 <= at && at < layout->count()){
                if(at){
                        layout->insertWidget(at, fw);
                }
                else{
                        layout->insertWidget(layout->count()-1, fw);
                }
                connect(fw, SIGNAL(selectedFrame(FrameWidget*)), this, SLOT(updateSelectedFrame(FrameWidget*)));
                connect(fw, SIGNAL(closeFrame(FrameWidget*)), this, SLOT(removeFrame(FrameWidget*)));
                connect(fw, SIGNAL(durationChanged(int)), this, SLOT(updateDuration(int)));
                updateSelectedFrame(fw);
                updateDuration(fw->getDuration());
        }
}

void TimeLineWidget::updateSelectedFrame(FrameWidget * fw){
        if(selectedFrame != nullptr && selectedFrame != fw)
                selectedFrame->unselectFrame();
        selectedFrame = fw;
        selectedFrame->selectFrame();
        update();
}

void TimeLineWidget::removeFrame(FrameWidget* fw){
        layout->removeWidget(fw);
        if(selectedFrame == fw)
                selectedFrame = nullptr;
        delete fw;
        fw = nullptr;
        update();
}

void TimeLineWidget::updateDuration(int change){
        duration += change;
        emit durationChanged(duration);
        emit setRange(0, duration);
        std::cout<<change<<" "<<duration<<std::endl;
}
