#ifndef GAMEEVENT_H
#define GAMEEVENT_H
#include "snake.h"
#include "function.h"
#include "omp.h"
#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QFile>
#include <algorithm>
#include<QInputDialog>
#include<QDir>
#include<QLine>

class gameEvent : public QWidget {
    Q_OBJECT
private:
    int score = 0, direction = left;
    snake* snakePtr = nullptr;
    coordinate foodCoordinate = coordinate(0, 0);
    bool isGift = false, inGame = false, flag = true, pause = false;
    QTimer* timer1 = new QTimer(this);
    QTimer* timer2 = new QTimer(this);
    const int SPEED = 100;
    const QString savedGamePath = "highScores.txt";

public:
    // hàm khởi tạo
    gameEvent(snake*);
    // hàm di chuyển rắn
    void move();
    // hàm kiểm tra va chạm, đi xuyên tường,...
    void checkCollision();
    // hàm ăn mồi
    void eat();
    // hàm trả về điểm của người chơi
    int getScore();
    // hàm đặt số điểm người chơi
    void setScore(int);
    // hàm đặt vị trí mồi (ngẫu nhiên)
    void localeFood();
    // hàm lưu điểm cao
    void saveHighScore(QString);
    // hàm lấy tên người chơi
    QString getPlayerName();
protected:
    // hàm thực hiện tác vụ đồ hoạ
    void paintEvent(QPaintEvent*);
    // hàm bắt các thao tác với bàn phím
    void keyPressEvent(QKeyEvent*);
public slots:
    // hàm khởi tạo trò chơi mới
    void init();
    // vòng lặp game
    void loop();
};

#endif // GAMEEVENT_H
