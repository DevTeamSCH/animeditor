#ifndef FRAMEELEMENT_H
#define FRAMEELEMENT_H

#include <QWidget>
#include "pixelwidget.h"
#include "pixelframe.h"

namespace Ui {
class FrameElement;
}

class FrameElement : public QWidget {
Q_OBJECT

public:
	explicit FrameElement(QWidget *parent = 0, unsigned x = -1, unsigned y = -1);

	~FrameElement();

	virtual QSize sizeHint() const override;

	virtual QSize minimumSizeHint() const override;

	void setX(unsigned x);

	void setY(unsigned y);

	unsigned getX();

	unsigned getY();

	QColor getColor();

private:
	//pointer to parent pixelframe, dont destroy here!!
	PixelFrame *frame;

	QVector<PixelWidget *> pixels;
	unsigned posX, posY;
	Ui::FrameElement *ui;

};

#endif // FRAMEELEMENT_H
