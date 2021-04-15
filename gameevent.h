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
    gameEvent(snake*);
    void move();
    void checkCollision();
    void eat();
    int getScore();
    void setScore(int);
    void localeFood();
    void saveHighScore(QString);
    QString getPlayerName();
protected:
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent*);
public slots:
    void init();
    void loop();
};

#endif // GAMEEVENT_H
