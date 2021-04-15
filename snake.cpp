#include "snake.h"

snake::snake()
{
    QVector<coordinate> v;
    v.push_back(coordinate(60, 60));
    v.push_back(coordinate(70, 60));
    v.push_back(coordinate(80, 60));
    snakeCoordinate = v;
}
snake::snake(QVector<coordinate> v)
{
    if (v.isEmpty()) {
        QVector<coordinate> temp;
        temp.push_back(coordinate(60, 60));
        temp.push_back(coordinate(70, 60));
        temp.push_back(coordinate(80, 60));
        snakeCoordinate = temp;
    }
    else {
        snakeCoordinate = v;
    }
}
void snake::setDirection(int direction)
{
    if ((this->direction == (direction + 2)) || (this->direction == (direction - 2))) {
        // does nothing
    }
    else {
        this->direction = direction;
    }
}
void snake::move()
{
    switch (direction) {
    case right: {
        coordinate head = snakeCoordinate.at(0);
        snakeCoordinate.push_front(coordinate(head.x + dotSize, head.y));
        snakeCoordinate.removeLast();
        break;
    }
    case left: {
        coordinate head = snakeCoordinate.at(0);
        snakeCoordinate.push_front(coordinate(head.x - dotSize, head.y));
        snakeCoordinate.removeLast();
        break;
    }
    case up: {
        coordinate head = snakeCoordinate.at(0);
        snakeCoordinate.removeLast();
        snakeCoordinate.push_front(coordinate(head.x, head.y - dotSize));
        break;
    }
    case down: {
        coordinate head = snakeCoordinate.at(0);
        snakeCoordinate.push_front(coordinate(head.x, head.y + dotSize));
        snakeCoordinate.removeLast();
        break;
    }
    }
}
QVector<coordinate> snake::getSnakeCoordinateVector()
{
    return snakeCoordinate;
}
void snake::eat()
{
    snakeCoordinate.push_back(snakeCoordinate.last());
}
void snake::setHeadCoordinate(coordinate c)
{
    snakeCoordinate[0] = c;
}
