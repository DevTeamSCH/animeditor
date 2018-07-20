#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pixelframe.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT

public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
        void setFrame(unsigned x,unsigned y);
        void setupCentralWidget();

private:
        PixelFrame *pf;
        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
