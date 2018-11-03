#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QColor>
#include <QGraphicsItem>

class Cell : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Cell(QColor color, int x, int y, int sceneWidth_, int sceneHeight_);
    explicit Cell(QObject *parent = nullptr);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    QColor get_color(){ return color_; }
    void set_color(QColor color){
        color_=color;
        update();
    }

signals:
    void RightClick(Cell * c);
    void LeftClick(Cell * c);
public slots:

private:
    QColor color_;
    int x_;
    int y_;
    int sceneWidth_;
    int sceneHeight_;
};

#endif // CELL_H
