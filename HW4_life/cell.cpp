#include "cell.h"
#include <QtWidgets>

Cell::Cell(QObject *parent) : QObject(parent)
{

}

Cell::Cell(QColor color, int x, int y, int sceneWidth, int sceneHeight){
    this->color_ = color;
    x_ = x * sceneWidth;
    y_ = y * sceneHeight;
    sceneWidth_ = sceneWidth;
    sceneHeight_ = sceneHeight;
}

/**
    sets the bounding rectangle of an object
    @param none
    @return QRectF
*/
QRectF Cell::boundingRect() const
{
    return QRectF(this->x_, this->y_, x_ + sceneWidth_, y_ + sceneHeight_);
}

/**
    sets the shape of an object
    @param none
    @return QPainterPath
*/
QPainterPath Cell::shape() const{
    QPainterPath path;
    path.addRect(this->x_, this->y_, x_ + sceneWidth_, y_ + sceneHeight_);
    return path;
}

/**
    void function to paint the cells and set brush color
    @param cell *QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget
    @return void
*/
void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);


    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_));

    painter->drawRect(QRect(this->x_, this->y_, x_ + sceneWidth_, y_ + sceneHeight_));

    painter->setBrush(b);
}

/**
    emits a rightclick or left click signal when a cell is pressed
    @param QGraphicsSceneMouseEvent *event
    @return void
*/
void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->buttons() == Qt::RightButton){ //right click
        emit RightClick(this);
    }
    if(event->buttons() == Qt::LeftButton){
        emit LeftClick(this);
    }

}
