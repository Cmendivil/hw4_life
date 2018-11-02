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


private slots:
    void on_newSampleButton_clicked();

private:
    Ui::LifeWindow *ui;
    QGraphicsScene *cellScene;
    Cell * cells[10][20];
    int height_;
    int width_;
    int turn_ = 0;
    int population_;
};

#endif // LIFEWINDOW_H
