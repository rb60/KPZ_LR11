#ifndef LAYERDRAWER_H
#define LAYERDRAWER_H

#include <QPaintDevice>
#include <QRect>
#include <QPointF>
#include <QRectF>
#include <QPainter>


class LayerDrawerContext
{
public:
    QRect area;
    QPaintDevice* canvas;
};

class LayerDrawer
{
protected:
    LayerDrawer* next;
    bool enabled = true;
    QColor color = Qt::black;
public:
    LayerDrawer(LayerDrawer* next, QColor color = Qt::black);
    virtual void draw(const LayerDrawerContext& context) = 0;
    LayerDrawer *getNext() const;
    void setNext(LayerDrawer *newNext);
    bool getEnabled() const;
    void setEnabled(bool newEnabled);
    QColor getColor() const;
    void setColor(const QColor &newColor);
    virtual ~LayerDrawer(){}
};

class LineLayer : public LayerDrawer
{
private:
    QPointF start;
    QPointF end;
public:
    LineLayer();
    LineLayer(const LineLayer& other);
    LineLayer(QPointF start, QPointF end, QColor color, LayerDrawer* next = nullptr);
    void draw(const LayerDrawerContext& context) override;
    QPointF getStart() const;
    void setStart(QPointF newStart);
    QPointF getEnd() const;
    void setEnd(QPointF newEnd);
    ~LineLayer() override {}
};

class ArcLayer : public LayerDrawer
{
private:
    QRectF rect;
    int startAngle;
    int spanAngle;
public:
    ArcLayer();
    ArcLayer(const ArcLayer& other);
    ArcLayer(const QRectF &rect, int startAngle, int spanAngle, QColor color, LayerDrawer* next = nullptr);
    void draw(const LayerDrawerContext& context) override;
    QRectF getRect() const;
    void setRect(const QRectF &newRect);
    int getStartAngle() const;
    void setStartAngle(int newStartAngle);
    int getSpanAngle() const;
    void setSpanAngle(int newSpanAngle);
    ~ArcLayer() override {}
};

#endif // LAYERDRAWER_H
