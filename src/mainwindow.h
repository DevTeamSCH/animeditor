#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static QColor BGColor; // Background color
    static QColor FGColor; // Foreground color
    static bool isPaintWindow; // false == pixel, true == window
    static bool isMousePressed; // Stores mouse state(used for mouse drag)

    // id of the current selected tool
    enum tool{
        Pointer,
        DrawFree,
        FillColor,
        DrawLine,
        DrawRect,
        DrawEllipse,
        DrawTextbtn
    };
    static tool activeTool;

private slots:
    void on_actionAbout_triggered();

    void on_action_Exit_triggered();

    void on_actionOpen_triggered();

    void setColor(QColor c); //sets current colorPreview's color

    void switchtoBG();

    void switchtoFG();

    void switchPaintUnit();

    void setTool(int);

private:
    Ui::MainWindow *ui;
    bool isFGSelected; // which colorPreview is selected
};

#endif // MAINWINDOW_H
