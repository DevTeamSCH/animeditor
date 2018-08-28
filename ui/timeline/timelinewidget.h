#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include <QWidget>
#include <QVector>
#include <QBoxLayout>

#include "framewidget.h"

namespace Ui {
class TimeLineWidget;
}

class TimeLineWidget : public QWidget
{
        Q_OBJECT

public:
        explicit TimeLineWidget(QWidget *parent = 0);
        ~TimeLineWidget();

//        virtual QSize sizeHint() const override;
//        virtual QSize minimumSizeHint() const override;

private:
        Ui::TimeLineWidget *ui;
        QVector< FrameWidget *> scene;
        QHBoxLayout *layout = new QHBoxLayout;
        FrameWidget* selectedFrame = nullptr;
        int duration = 0;

public slots:
        void addFrame(FrameWidget* fw = new FrameWidget("Frame", 1000), int at = 0);
        void updateSelectedFrame(FrameWidget* fw);
        void removeFrame(FrameWidget* fw);
        void updateDuration(int change);
signals:
        void durationChanged(int duration);
        void setRange(int min, int max);
};

#endif // TIMELINEWIDGET_H
