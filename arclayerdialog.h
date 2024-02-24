#ifndef ARCLAYERDIALOG_H
#define ARCLAYERDIALOG_H

#include <QDialog>
#include "layerdrawer.h"

namespace Ui {
class ArcLayerDialog;
}

class ArcLayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ArcLayerDialog(QWidget *parent = nullptr);
    ~ArcLayerDialog();

    ArcLayer getLayer() const;
    void setLayer(const ArcLayer &newLayer);

public slots:
    void topLeftXUpdate(double value);
    void topLeftYUpdate(double value);
    void bottomRightXUpdate(double value);
    void bottomRightYUpdate(double value);
    void startAngleUpdate(int value);
    void spanAngleUpdate(int value);
    void setColor();

private:
    ArcLayer layer;
    Ui::ArcLayerDialog *ui;
};

#endif // ARCLAYERDIALOG_H
