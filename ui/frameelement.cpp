#include "frameelement.h"
#include "ui_frameelement.h"
#include <QGridLayout>

//Creates a frame element with 4 pixelwidget

FrameElement::FrameElement(QWidget *parent, unsigned x, unsigned y) : QWidget(parent), posX(x), posY(y),
								      ui(new Ui::FrameElement)
{
	frame = (PixelFrame *) parent;
	QGridLayout *layout = new QGridLayout();
	layout->setSpacing(1);
	layout->setMargin(0);

	setMaximumSize(21, 21);

	for (int i = 0; i < 4; i++) {
		pixels.append(new PixelWidget(this, i));
		layout->addWidget(pixels[i], i / 2, i % 2);
	}

	this->setLayout(layout);
	ui->setupUi(this);
}

//Recommended size, computed from the pixelwidgets it cointains

QSize FrameElement::sizeHint() const
{
	if (!pixels.empty())
		return QSize(pixels[0]->sizeHint().height() * 2, pixels[0]->sizeHint().width() * 2);
	else
		return minimumSizeHint();
}

QSize FrameElement::minimumSizeHint() const
{
	return QSize(25, 25);
}

FrameElement::~FrameElement()
{
	delete ui;
}

void FrameElement::setX(unsigned x)
{
	posX = x;
}

void FrameElement::setY(unsigned y)
{
	posY = y;
}

unsigned FrameElement::getX()
{
	return posX;
}

unsigned FrameElement::getY()
{
	return posY;
}

// Gets the drawing color from the frame

QColor FrameElement::getColor()
{
	return frame->getDrawColor();
}
