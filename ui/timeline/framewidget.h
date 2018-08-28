#ifndef FRAMEWIDGET_H
#define FRAMEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QColor>

namespace Ui {
class FrameWidget;
}

class FrameWidget : public QWidget
{
        Q_OBJECT

public:



        explicit FrameWidget(QWidget *parent = 0);
        explicit FrameWidget( QString name, unsigned int duration = 1000, QWidget *parent = 0);
        virtual QSize sizeHint() const override;
        virtual QSize minimumSizeHint() const override;
        void selectFrame();
        void unselectFrame();
        int getDuration();
        ~FrameWidget();

protected:
//        void paintEvent(QPaintEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
private:
        int x = 0 , y = 0, width = 200, height = 115;
//    int marginX = 5, marginY = 5;
        QString name;
        int duration;
        Ui::FrameWidget *ui;
        QColor unselectedColor = QColor(216, 216, 216);
        QColor selectedColor = QColor(181, 209, 255);
        void setColor(QColor color);


        void init();
public slots:
        void updateName(QString name);
        void updateDuration(int duration);
        void Close();
signals:
        void selectedFrame(FrameWidget* fw);
        void closeFrame(FrameWidget* fw);
        void durationChanged(int change);
};

#endif // FRAMEWIDGET_H
