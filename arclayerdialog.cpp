#include "arclayerdialog.h"
#include "ui_arclayerdialog.h"
#include <QMenuBar>
#include <QColorDialog>

ArcLayerDialog::ArcLayerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArcLayerDialog)
{
    ui->setupUi(this);

    connect(ui->leftTopX, SIGNAL(valueChanged(double)), SLOT(topLeftXUpdate(double)));
    connect(ui->leftTopY, SIGNAL(valueChanged(double)), SLOT(topLeftYUpdate(double)));
    connect(ui->rightBottomX, SIGNAL(valueChanged(double)), SLOT(bottomRightXUpdate(double)));
    connect(ui->rightBottomY, SIGNAL(valueChanged(double)), SLOT(bottomRightYUpdate(double)));
    connect(ui->startAngle, SIGNAL(valueChanged(int)), SLOT(startAngleUpdate(int)));
    connect(ui->spanAngle, SIGNAL(valueChanged(int)), SLOT(spanAngleUpdate(int)));
    connect(ui->setColor, SIGNAL(clicked()), SLOT(setColor()));

    QMenuBar* menu = new QMenuBar(this);
    menu->addAction("Save", this, SLOT(accept()));
    menu->addAction("Canel", this, SLOT(reject()));
    this->layout()->setMenuBar(menu);
}

ArcLayerDialog::~ArcLayerDialog()
{
    delete ui;
}

ArcLayer ArcLayerDialog::getLayer() const
{
    return layer;

}

void ArcLayerDialog::setLayer(const ArcLayer &newLayer)
{
    layer = newLayer;
    ui->leftTopX->setValue(layer.getRect().left());
    ui->leftTopY->setValue(layer.getRect().top());
    ui->rightBottomX->setValue(layer.getRect().right());
    ui->rightBottomY->setValue(layer.getRect().bottom());
    ui->startAngle->setValue(layer.getStartAngle());
    ui->spanAngle->setValue(layer.getSpanAngle());

}

void ArcLayerDialog::topLeftXUpdate(double value)
{
    QRectF r = layer.getRect();
    r.setLeft(value);
    layer.setRect(r);
}

void ArcLayerDialog::topLeftYUpdate(double value)
{
    QRectF r = layer.getRect();
    r.setTop(value);
    layer.setRect(r);
}

void ArcLayerDialog::bottomRightXUpdate(double value)
{
    QRectF r = layer.getRect();
    r.setRight(value);
    layer.setRect(r);
}

void ArcLayerDialog::bottomRightYUpdate(double value)
{
    QRectF r = layer.getRect();
    r.setTop(value);
    layer.setRect(r);
}

void ArcLayerDialog::startAngleUpdate(int value)
{
    layer.setStartAngle(value);
}

void ArcLayerDialog::spanAngleUpdate(int value)
{
    layer.setSpanAngle(value);
}

void ArcLayerDialog::setColor()
{
    QColor color = QColorDialog::getColor();
    if(color.isValid())
    {
        layer.setColor(color);
    }
}
