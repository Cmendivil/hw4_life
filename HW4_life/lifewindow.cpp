#include "lifewindow.h"
#include "ui_lifewindow.h"
#include <iostream>

LifeWindow::LifeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LifeWindow)
{
    cellScene = new QGraphicsScene;
    ui->setupUi(this);
    QGraphicsView* cellView = ui->cellView;
    cellView->setScene(cellScene);
    cellView->setSceneRect(0,0,cellView->frameSize().width()-10,cellView->frameSize().height()-10);
    height_ = cellView->frameSize().height() - 10;
    width_ = cellView->frameSize().width() - 10;
    for(int i = 0; i < cellView->frameSize().width(); i = i + width_/20) {
        cellScene->addLine(i, 0, i, height_);
    }
    for(int i = 0; i < cellView->frameSize().height(); i = i +height_/10) {
        cellScene->addLine(0, i, width_, i);
    }

    srand(time(0));
    populate();
}

LifeWindow::~LifeWindow()
{
    delete ui;
}

void LifeWindow::populate(){
    QColor color(255, 0, 0);
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 20; j++) {
            if(rand() % 100 < 50) {
                color.setRgb(66, 158, 244);
                population_++;
            } else{
                color.setRgb(255, 255, 255);
            }
            Cell * item = new Cell(color, j, i, width_/20, height_/10);
            cells[i][j] = item;
            cellScene->addItem(item);
        }
    }

}

void LifeWindow::on_newSampleButton_clicked()
{
    populate();
}
