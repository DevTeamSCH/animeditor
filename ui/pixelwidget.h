#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QColor>


namespace Ui {
class PixelWidget;
}

class PixelWidget : public QWidget {
Q_OBJECT

public:
	explicit PixelWidget(QWidget *parent = 0, unsigned p = -1);

	PixelWidget(int size, QWidget *parent = 0);

	~PixelWidget();

	void setSquareSize(int size);

	virtual QSize sizeHint() const override;

	virtual QSize minimumSizeHint() const override;

	void setPos(unsigned);

	unsigned getPos();

public slots:

signals:

	QColor getActualColor();

protected:
	void mousePressEvent(QMouseEvent *event) override;

	void mouseMoveEvent(QMouseEvent *event) override;

	void paintEvent(QPaintEvent *event) override;

private:
	Ui::PixelWidget *ui;
	unsigned pos;
	QColor color = QColor(0, 0, 0);
	int squareSize = 20;

};

#endif // WIDGET_H
