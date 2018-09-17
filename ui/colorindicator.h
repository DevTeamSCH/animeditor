#ifndef COLORINDICATOR_H
#define COLORINDICATOR_H

#include <QWidget>

namespace Ui {
class ColorIndicator;
}

class ColorIndicator : public QWidget {
Q_OBJECT
public:
	explicit ColorIndicator(QWidget *parent = 0);

	~ColorIndicator();

	QSize sizeHint() const override;

private:
	// Ui::ColorIndicator *ui;

	QColor actual, before;

	void mousePressEvent(QMouseEvent *) override;

	void paintEvent(QPaintEvent *) override;

public slots:

	void updateColor(QColor color);


signals:

	void colorChanged(QColor);
};

#endif // COLORINDICATOR_H
