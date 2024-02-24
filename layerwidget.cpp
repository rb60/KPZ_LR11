#include "layerwidget.h"
#include <QResizeEvent>

LayerDrawer *LayerWidget::getRoot() const
{
    return root;
}

void LayerWidget::setRoot(LayerDrawer *newRoot)
{
    root = newRoot;
}

QRect LayerWidget::getArea() const
{
    return area;
}

void LayerWidget::setArea(const QRect &newArea)
{
    area = newArea;
}

LayerWidget::LayerWidget(QWidget *parent)
    : QWidget{parent}
{

}

void LayerWidget::paintEvent(QPaintEvent *pe)
{
    LayerDrawerContext context;
    context.area = area;
    context.canvas = this;
    if(root != nullptr)
    {
        root->draw(context);
    }
}

void LayerWidget::resizeEvent(QResizeEvent *event)
{
    area = QRect(QPoint(0,0), event->size());
}
