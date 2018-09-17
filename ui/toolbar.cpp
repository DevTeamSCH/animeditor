#include "toolbar.h"
#include "ui_toolbar.h"


Toolbar::Toolbar(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Toolbar)
{
	ui->setupUi(this);
}

Toolbar::~Toolbar()
{
	delete ui;
}

void Toolbar::on_brushButton_clicked()
{
	QPixmap pixm(":/images/brushicon");
	setCursor(pixm);
	emit toolChanged(Brush);
}

void Toolbar::on_arrowButton_clicked()
{
	setCursor(Qt::ArrowCursor);
	emit toolChanged(Arrow);
}

void Toolbar::on_lineButton_clicked()
{
	setCursor(Qt::CrossCursor);
	emit toolChanged(Line);
}

void Toolbar::on_rectButton_clicked()
{
	setCursor(Qt::CrossCursor);
	emit toolChanged(Rectangle);
}

void Toolbar::on_ellipseButton_clicked()
{
	setCursor(Qt::CrossCursor);
	emit toolChanged(Ellipse);
}

void Toolbar::on_pipetteButton_clicked()
{
	QPixmap pixm(":/images/pipette");
	setCursor(pixm);
	emit toolChanged(Pipette);
}

QSize Toolbar::sizeHint() const
{
	return QSize(40, 200);
}

void Toolbar::on_fillButton_clicked()
{
	emit toolChanged(Fill);
}

void Toolbar::on_textButton_clicked()
{
	emit toolChanged(Text);
}

void Toolbar::on_brushButton_toggled(bool checked)
{
	on_brushButton_clicked();
}
