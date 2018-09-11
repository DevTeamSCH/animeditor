#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pixelframe.h"

#include "timeline/timelinebar.h"

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

        void mouseMoveEvent(QMouseEvent *event) override;
private:
        PixelFrame *pf;
        TimeLineBar* tlb = nullptr;
        void setupCentralWidget();
        void setupRightSide();
        void setupSouthWidget();
        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
