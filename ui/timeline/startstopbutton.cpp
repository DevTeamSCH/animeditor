#include "startstopbutton.h"
#include "ui_startstopbutton.h"

StartStopButton::StartStopButton(QWidget *parent) :
    QPushButton(parent),
    ui(new Ui::StartStopButton)
{
    ui->setupUi(this);
}

StartStopButton::~StartStopButton()
{
    delete ui;
}
