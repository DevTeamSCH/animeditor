#ifndef PIXELFRAME_H
#define PIXELFRAME_H

#include <QWidget>
#include "toolbar.h"

namespace Ui {
class PixelFrame;
}

class PixelFrame : public QWidget {
Q_OBJECT

public:

	explicit PixelFrame(unsigned sizeX, unsigned sizeY, QWidget *parent = 0);

	~PixelFrame();

	QColor getDrawColor();

	QSize sizeHint() const override;

//        QSize minimumSizeHint() const override;

private:
	Ui::PixelFrame *ui;
	unsigned x, y;
	QColor drawColor;
	ToolState ts = Arrow;

public slots:

	void updateColor(QColor);

	void setTool(ToolState);
};

#endif // PIXELFRAME_H
