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

QRectF Cell::boundingRect() const
{
    return QRectF(this->x_, this->y_, x_ + sceneWidth_, y_ + sceneHeight_);
}

QPainterPath Cell::shape() const{
    QPainterPath path;
    path.addRect(this->x_, this->y_, x_ + sceneWidth_, y_ + sceneHeight_);
    return path;
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);


    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_.dark(option->state & QStyle::State_Sunken ? 120 : 100)));

    painter->drawRect(QRect(this->x_, this->y_, x_ + sceneWidth_, y_ + sceneHeight_));
    qDebug() << "x: " << x_;
    qDebug() << "width: " << sceneWidth_;
    qDebug() << "y: " << y_;
    qDebug() << "height: " << sceneHeight_;

    painter->setBrush(b);
}
