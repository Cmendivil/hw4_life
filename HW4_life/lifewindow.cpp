#include "lifewindow.h"
#include "ui_lifewindow.h"
#include <iostream>
#include <QDebug>
#include <QTimer>

LifeWindow::LifeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LifeWindow)
{
    cellScene = new QGraphicsScene;
    barScene = new QGraphicsScene;
    ui->setupUi(this);
    QGraphicsView* cellView = ui->cellView;
    QGraphicsView* barView = ui->barView;
    cellView->setScene(cellScene);
    cellView->setSceneRect(0,0,cellView->frameSize().width()-10,cellView->frameSize().height()-10);
    cellHeight_ = cellView->frameSize().height() - 10;
    cellWidth_ = cellView->frameSize().width() - 10;
    for(int i = 0; i < cellView->frameSize().width(); i = i + cellWidth_/20) {
        cellScene->addLine(i, 0, i, cellHeight_);
    }
    for(int i = 0; i < cellView->frameSize().height(); i = i + cellHeight_/10) {
        cellScene->addLine(0, i, cellWidth_, i);
    }
    ui->speed->setText(QString("Speed: ")+QString::number(speed_, 'f', 6));

    srand(time(0));
    barView->setScene(barScene);
    barHeight_ = barView->frameSize().height() - 10;
    barWidth_ = barView->frameSize().width() - 10;
    barView->setSceneRect(0,0,barWidth_,barHeight_);

    for(int i = 0; i < 20; i++) { //initilize bars_
        bars_[i] = 0.0;
    }

    populate();

    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(on_playButton_clicked()));


}

LifeWindow::~LifeWindow()
{
    delete ui;
}

void LifeWindow::populate(){
    turn_=0;
    population_=0;
    QColor color(255, 0, 0);
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 20; j++) {
            if(rand() % 100 < 50) {
                color.setRgb(66, 158, 244);
                population_++;
            } else{
                color.setRgb(255, 255, 255);
            }
            Cell * item = new Cell(color, j, i, cellWidth_/20, cellHeight_/10);
            cells[i][j] = item;
            cellScene->addItem(item);
            connect(item, &Cell::RightClick, this, &LifeWindow::RightClickSlot);
            connect(item, &Cell::LeftClick, this, &LifeWindow::LeftClickSlot);
        }
    }
    GenerateBars();
    ui->turn->setText(QString("Turn: 0"));
    ui->population->setText(QString("Population: ")+QString::number(population_)+QString(" (")+QString::number((population_*100)/200)+QString("%)"));
}

void LifeWindow::TakeTurn(){
   IncreaseTurn();
   RepaintCells();
   GenerateBars();
}

void LifeWindow::RepaintCells(){
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 20; j++) {
            if(cells[i][j]->get_color() == QColor(255,0,0)){
                cells[i][j]->set_color(QColor(66, 158, 244));
            }
        }
    }
    cellScene->update();
}

void LifeWindow::GenerateBars(){
    if(bars_[19] != 0.0){
        barScene->clear();
        barScene->update();
        for(int i = 0; i < 19; i++) {
            bars_[i] = bars_[i+1];
            barScene->addRect(i*(barWidth_/20), (barHeight_)*(1-(bars_[i])), barWidth_/20 , barHeight_);
        }
        bars_[19] = population_/200.0;
        barScene->addRect(19*(barWidth_/20), (barHeight_)*(1-(bars_[19])), barWidth_/20 , barHeight_);
        return;
    }

    for(int i = 0; i < 20; i++) {
        if(bars_[i] == 0.0) {
            bars_[i] = population_/200.0;
            barScene->addRect(i*(barWidth_/20), (barHeight_)*(1-(bars_[i])), barWidth_/20 , barHeight_);
            return;
        }
    }
}

void LifeWindow::on_newSampleButton_clicked()
{
    populate();
    for(int i = 0; i < 20; i++) { //reset bars
        bars_[i] = 0.0;
    }
    barScene->clear(); //clear the bars
    barScene->update();
}

void LifeWindow::on_stepButton_clicked()
{
    TakeTurn();
}

void LifeWindow::on_speedSlider_valueChanged(int value)
{
    speed_ = 1-(value/100.0);
    ui->speed->setText(QString("Speed: ")+QString::number(speed_, 'f', 6));
}

void LifeWindow::LeftClickSlot(Cell * c){
    if (c->get_color() == QColor(255, 255, 255)){
        population_++;
        ui->population->setText(QString("Population: ")+QString::number(population_)+QString(" (")+QString::number((population_*100)/200)+QString("%)"));
        c->set_color(QColor(255,0,0));
    }
}

void LifeWindow::RightClickSlot(Cell * c){
    if (c->get_color() != QColor(255, 255, 255)){
        population_--;
        ui->population->setText(QString("Population: ")+QString::number(population_)+QString(" (")+QString::number((population_*100)/200)+QString("%)"));
        c->set_color(QColor(255,255,255));
    }
}

void LifeWindow::on_playButton_clicked()
{
    TakeTurn();
    timer->start(speed_*1000);
}

void LifeWindow::IncreaseTurn(){
    turn_++;
    ui->turn->setText(QString("Turn: ")+QString::number(turn_));
}

void LifeWindow::on_pauseButton_clicked()
{
    timer->stop();
}
