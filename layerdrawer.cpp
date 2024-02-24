#include "layerdrawer.h"

LayerDrawer *LayerDrawer::getNext() const
{
    return next;
}

void LayerDrawer::setNext(LayerDrawer *newNext)
{
    next = newNext;
}

bool LayerDrawer::getEnabled() const
{
    return enabled;
}

void LayerDrawer::setEnabled(bool newEnabled)
{
    enabled = newEnabled;
}

QColor LayerDrawer::getColor() const
{
    return color;
}

void LayerDrawer::setColor(const QColor &newColor)
{
    color = newColor;
}

LayerDrawer::LayerDrawer(LayerDrawer* next, QColor color) : next(next) , color(color){}

QPointF LineLayer::getStart() const
{
    return start;
}

void LineLayer::setStart(QPointF newStart)
{
    start = newStart;
}

QPointF LineLayer::getEnd() const
{
    return end;
}

void LineLayer::setEnd(QPointF newEnd)
{
    end = newEnd;
}


void LineLayer::draw(const LayerDrawerContext& context)
{

    if(enabled)
    {
        QPointF concreteStart((float)(context.area.width()) * start.x(), (float)(context.area.height()) * start.y());
        QPointF concreteEnd((float)(context.area.width()) * end.x(), (float)(context.area.height()) * end.y());
        concreteStart += context.area.topLeft();
        concreteEnd += context.area.topLeft();

        QPainter p(context.canvas);
        p.setPen(QPen(color, 10));
        p.drawLine(concreteStart, concreteEnd);
        p.end();
    }


    if(next != nullptr)
    {
        next->draw(context);
    }
}

int ArcLayer::getStartAngle() const
{
    return startAngle;
}

void ArcLayer::setStartAngle(int newStartAngle)
{
    startAngle = newStartAngle;
}

int ArcLayer::getSpanAngle() const
{
    return spanAngle;
}

void ArcLayer::setSpanAngle(int newSpanAngle)
{
    spanAngle = newSpanAngle;
}


QRectF ArcLayer::getRect() const
{
    return rect;
}

void ArcLayer::setRect(const QRectF &newRect)
{
    rect = newRect;
}

void ArcLayer::draw(const LayerDrawerContext& context)
{
    if(enabled)
    {
        QPointF concreteTopLeft((float)(context.area.width()) * rect.topLeft().x(), (float)(context.area.height()) * rect.topLeft().y());
        QPointF concreteBottomRight((float)(context.area.width()) * rect.bottomRight().x(), (float)(context.area.height()) * rect.bottomRight().y());
        concreteTopLeft += context.area.topLeft();
        concreteBottomRight += context.area.topLeft();
        QRectF concreteRect(concreteTopLeft, concreteBottomRight);

        QPainter p(context.canvas);
        p.setPen(QPen(color, 10));
        p.drawArc(concreteRect, startAngle, spanAngle);
        p.end();
    }

    if(next != nullptr)
    {
        next->draw(context);
    }
}

ArcLayer::ArcLayer() : ArcLayer(QRectF(0,0,1,1),0, 5760, Qt::black)
{

}

ArcLayer::ArcLayer(const ArcLayer &other) : ArcLayer(other.rect, other.startAngle, other.spanAngle, other.color, other.next)
{

}

ArcLayer::ArcLayer(const QRectF &rect, int startAngle, int spanAngle, QColor color, LayerDrawer* next) : LayerDrawer(next, color),  rect(rect),
    startAngle(startAngle),
    spanAngle(spanAngle)
{}

LineLayer::LineLayer() : LineLayer(QPointF(0,0), QPointF(1,1), Qt::black)
{

}

LineLayer::LineLayer(const LineLayer &other) : LineLayer(other.start, other.end, other.color ,other.next)
{

}

LineLayer::LineLayer(QPointF start, QPointF end, QColor color, LayerDrawer* next) : LayerDrawer(next, color), start(std::move(start)),
    end(std::move(end))
{}
