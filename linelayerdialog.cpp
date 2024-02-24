#include "linelayerdialog.h"
#include "ui_linelayerdialog.h"
#include <QMenuBar>
#include <QColorDialog>

LineLayerDialog::LineLayerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LineLayerDialog)
{
    ui->setupUi(this);

    connect(ui->startX, SIGNAL(valueChanged(double)), SLOT(startX_Update(double)));
    connect(ui->startY, SIGNAL(valueChanged(double)), SLOT(startY_Update(double)));
    connect(ui->endX, SIGNAL(valueChanged(double)), SLOT(endX_Update(double)));
    connect(ui->endY, SIGNAL(valueChanged(double)), SLOT(endY_Update(double)));
    connect(ui->setColorButton, SIGNAL(clicked()), SLOT(setColor()));


    QMenuBar* menu = new QMenuBar(this);
    menu->addAction("Save", this, SLOT(accept()));
    menu->addAction("Canel", this, SLOT(reject()));
    this->layout()->setMenuBar(menu);
}

LineLayerDialog::~LineLayerDialog()
{
    delete ui;
}

LineLayer LineLayerDialog::getLayer() const
{
    return layer;
}

void LineLayerDialog::setLayer(const LineLayer &newLayer)
{
    layer = newLayer;
    ui->endX->setValue(layer.getEnd().x());
    ui->endY->setValue(layer.getEnd().y());
    ui->startX->setValue(layer.getStart().x());
    ui->startY->setValue(layer.getStart().y());
}

void LineLayerDialog::startX_Update(double value)
{
    layer.setStart(QPointF(value, layer.getStart().y()));
}

void LineLayerDialog::startY_Update(double value)
{
    layer.setStart(QPointF(layer.getStart().x(), value));
}

void LineLayerDialog::endX_Update(double value)
{
    layer.setEnd(QPointF(value, layer.getEnd().y()));
}

void LineLayerDialog::endY_Update(double value)
{
    layer.setEnd(QPointF(layer.getEnd().x(), value));
}

void LineLayerDialog::setColor()
{
    QColor color = QColorDialog::getColor();
    if(color.isValid())
    {
        layer.setColor(color);
    }


}

