#ifndef TIMESLIDER_H
#define TIMESLIDER_H

#include <QSlider>
#include <QWidget>

namespace Ui {
class TimeSlider;
}

class TimeSlider : public QSlider
{
    Q_OBJECT

public:
    explicit TimeSlider(QWidget *parent = nullptr);
    ~TimeSlider();

private:
    Ui::TimeSlider *ui;

    void init();
};

#endif // TIMESLIDER_H
