#ifndef LAYERWIDGET_H
#define LAYERWIDGET_H

#include <QWidget>
#include "layerdrawer.h"


class LayerWidget : public QWidget
{
    Q_OBJECT
private:
    LayerDrawer* root = nullptr;
    QRect area;
public:
    explicit LayerWidget(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent* pe);
    virtual void resizeEvent(QResizeEvent *event);

    LayerDrawer *getRoot() const;
    void setRoot(LayerDrawer *newRoot);
    QRect getArea() const;
    void setArea(const QRect &newArea);

signals:

};

#endif // LAYERWIDGET_H
