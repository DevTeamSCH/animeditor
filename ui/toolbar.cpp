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
    QPixmap pixm(":/resources/brush.png");
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

void Toolbar::on_toolButton_6_clicked()
{
     QPixmap pixm(":/resources/pipette.png");
     setCursor(pixm);
     emit toolChanged(Pipette);
}

QSize Toolbar::sizeHint() const{
        return QSize(40,200);
}
