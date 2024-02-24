#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->addCombo->addItem("Line");
    ui->addCombo->addItem("Arc");
    lineDialog = new LineLayerDialog(this);
    arcDialog = new ArcLayerDialog(this);

    connect(ui->addButton, SIGNAL(clicked()), SLOT(add()));
    connect(ui->moveUp, SIGNAL(clicked()), SLOT(moveLayerUp()));
    connect(ui->moveDown, SIGNAL(clicked()), SLOT(moveLayerDown()));
    connect(ui->editButton, SIGNAL(clicked()), SLOT(editLayer()));
    connect(ui->removeButton, SIGNAL(clicked()), SLOT(removeLayer()));
    connect(ui->enabdleDisable, SIGNAL(clicked()), SLOT(enableDisableLayer()));

}

MainWindow::~MainWindow()
{
    delete ui;
    for(int i = 0; i < list.size(); i++)
    {
        delete list[i];
    }
}

void MainWindow::add()
{

    LayerDrawer* newLayer = nullptr;
    switch (ui->addCombo->currentIndex()) {
    case 0:
    {
        lineDialog->setLayer(LineLayer());
        if(lineDialog->exec() == QDialog::Accepted)
        {
            newLayer = new LineLayer(lineDialog->getLayer());
            ui->layerList->insertItem(0, "Line");
        }
        break;
    }
    case 1:
    {
        arcDialog->setLayer(ArcLayer());
        if(arcDialog->exec() == QDialog::Accepted)
        {
            newLayer = new ArcLayer(arcDialog->getLayer());
            ui->layerList->insertItem(0, "Arc");
        }
        break;
    }
    default:
        break;
    }

    if(newLayer != nullptr)
    {
        if(list.size() != 0)
        {
            list.front()->setNext(newLayer);
        }
        list.push_front(newLayer);
        ui->layerWidget->setRoot(list.back());
    }

}

void MainWindow::moveLayerUp()
{

    int index = ui->layerList->currentRow();
    if(index > 0)
    {
        if(index < list.size() - 1)
        {
            list[index + 1]->setNext(list[index - 1]);
        }
        list[index]->setNext(index > 1 ? list[index - 2] : nullptr);
        list[index - 1]->setNext(list[index]);

        list.swapItemsAt(index, index - 1);

        QListWidgetItem* current =  ui->layerList->takeItem(index);
        ui->layerList->insertItem(index - 1, current);
        ui->layerWidget->setRoot(list.back());
        update();
    }


}

void MainWindow::moveLayerDown()
{
    int index = ui->layerList->currentRow();
    if(index < list.size() - 1)
    {
        if(index < list.size() - 2)
        {
            list[index + 2]->setNext(list[index]);
        }
        list[index + 1]->setNext(index > 0 ? list[index - 1] : nullptr);
        list[index]->setNext(list[index + 1]);

        list.swapItemsAt(index, index + 1);

        QListWidgetItem* current =  ui->layerList->takeItem(index);
        ui->layerList->insertItem(index + 1, current);
        ui->layerWidget->setRoot(list.back());
        update();
    }
}

void MainWindow::editLayer()
{
    int index = ui->layerList->currentRow();
    if(index < 0)
    {
        return;
    }
    QString current = ui->layerList->currentItem()->text();

    if(current == "Line")
    {
        lineDialog->setLayer(*((LineLayer*)(list[index])));
        if(lineDialog->exec() == QDialog::Accepted)
        {
            *((LineLayer*)(list[index])) = lineDialog->getLayer();
        }
    }
    else if(current == "Arc")
    {
        arcDialog->setLayer(*((ArcLayer*)(list[index])));
        if(arcDialog->exec() == QDialog::Accepted)
        {
            *((ArcLayer*)(list[index])) = arcDialog->getLayer();
        }
    }
}

void MainWindow::removeLayer()
{
    int index = ui->layerList->currentRow();
    if(index < 0)
    {
        return;
    }

    if(index < list.size() - 1)
    {
        list[index + 1]->setNext(index > 0 ? list[index - 1] : nullptr);
    }

    ui->layerWidget->setRoot(nullptr);
    delete list[index];
    list.remove(index);
    if(list.size() > 0)
    {
        ui->layerWidget->setRoot(list.back());
    }
    delete ui->layerList->takeItem(index);
    update();

}

void MainWindow::enableDisableLayer()
{
    int index = ui->layerList->currentRow();
    if(index >= 0)
    {
        list[index]->setEnabled(!list[index]->getEnabled());
        update();
    }

}

