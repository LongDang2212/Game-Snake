#ifndef SNAKE_H
#define SNAKE_H

#include "function.h"
#include <QVector>

// class rắn
class snake {
private:

    int direction = left;
    // vector chứa các toạ độ của rắn
    QVector<coordinate> snakeCoordinate;

public:
    snake();
    snake(QVector<coordinate>);
    // hàm di chuyển của rắn
    void move();
    // hàm đặt hướng đi
    void setDirection(int);
    // hàm lấy vector toạ độ
    QVector<coordinate> getSnakeCoordinateVector();
    // hàm ăn mồi (tăng độ dài)
    void eat();
    // hàm đặt vị trí đầu rắn
    void setHeadCoordinate(coordinate);
};

#endif // SNAKE_H
