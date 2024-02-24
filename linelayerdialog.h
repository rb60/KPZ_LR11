#ifndef LINELAYERDIALOG_H
#define LINELAYERDIALOG_H

#include <QDialog>
#include "layerdrawer.h"

namespace Ui {
class LineLayerDialog;
}

class LineLayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LineLayerDialog(QWidget *parent = nullptr);
    ~LineLayerDialog();

    LineLayer getLayer() const;
    void setLayer(const LineLayer &newLayer);

public slots:
    void startX_Update(double value);
    void startY_Update(double value);
    void endX_Update(double value);
    void endY_Update(double value);
    void setColor();

private:
    LineLayer layer;
    Ui::LineLayerDialog *ui;
};

#endif // LINELAYERDIALOG_H
