#ifndef LIFEWINDOW_H
#define LIFEWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "cell.h"

namespace Ui {
class LifeWindow;
}

class LifeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LifeWindow(QWidget *parent = nullptr);
    ~LifeWindow();
    void populate();
    void IncreaseTurn();


private slots:
    void on_newSampleButton_clicked();

    void on_stepButton_clicked();

    void on_speedSlider_valueChanged(int value);

    void on_playButton_clicked();

    void on_pauseButton_clicked();

public slots:
    void RightClickSlot(Cell * c);
    void LeftClickSlot(Cell * c);

private:
    Ui::LifeWindow *ui;
    QGraphicsScene *cellScene;
    QGraphicsScene *barScene;
    QTimer *timer;
    Cell * cells[10][20];
    int height_;
    int width_;
    int turn_ = 0;
    int population_ = 0;
    double speed_ = 1.0;
};

#endif // LIFEWINDOW_H
