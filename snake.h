#ifndef SNAKE_H
#define SNAKE_H

#include "function.h"
#include <QVector>

class snake {
private:

    int direction = left;

    QVector<coordinate> snakeCoordinate;

public:
    snake();
    snake(QVector<coordinate>);
    void move();
    void setDirection(int);
    QVector<coordinate> getSnakeCoordinateVector();
    void eat();
    void setHeadCoordinate(coordinate);
};

#endif // SNAKE_H
