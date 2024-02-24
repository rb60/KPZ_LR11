#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "layerdrawer.h"
#include "linelayerdialog.h"
#include "arclayerdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void add();
    void moveLayerUp();
    void moveLayerDown();
    void editLayer();
    void removeLayer();
    void enableDisableLayer();

private:
    LineLayerDialog* lineDialog;
    ArcLayerDialog* arcDialog;
    QList<LayerDrawer*> list;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
