#ifndef TIMELABEL_H
#define TIMELABEL_H

#include <QLabel>

namespace Ui {
class TimeLabel;
}

class TimeLabel : public QLabel
{
    Q_OBJECT

public:
    explicit TimeLabel(QWidget *parent = nullptr);
    ~TimeLabel();

private:
    Ui::TimeLabel *ui;
    QString startText = "0:0:0";

    void init();

public slots:
        void milisecToTime(int milisec);

};

#endif // TIMELABEL_H
