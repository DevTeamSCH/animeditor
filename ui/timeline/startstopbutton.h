#ifndef STARTSTOPBUTTON_H
#define STARTSTOPBUTTON_H

#include <QPushButton>

namespace Ui {
class StartStopButton;
}

class StartStopButton : public QPushButton
{
    Q_OBJECT

public:
    explicit StartStopButton(QWidget *parent = nullptr);
    ~StartStopButton();

private:
    Ui::StartStopButton *ui;
};

#endif // STARTSTOPBUTTON_H
