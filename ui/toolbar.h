#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>

namespace Ui {
class Toolbar;
}

enum ToolState{
        Arrow,
        Brush,
        Line,
        Rectangle,
        Ellipse,
        Pipette
};

class Toolbar : public QWidget
{
        Q_OBJECT

public:
        explicit Toolbar(QWidget *parent = 0);
        ~Toolbar();

        QSize sizeHint() const override;

private slots:
        void on_brushButton_clicked();

        void on_arrowButton_clicked();

        void on_lineButton_clicked();

        void on_rectButton_clicked();

        void on_ellipseButton_clicked();

        void on_pipetteButton_clicked();

signals:
        void toolChanged(ToolState);
private:
        Ui::Toolbar *ui;
};

#endif // TOOLBAR_H
