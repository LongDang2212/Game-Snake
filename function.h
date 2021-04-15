#ifndef FUNCTION_H
#define FUNCTION_H

#include <QTime>
#include <QRandomGenerator>

static const int dotSize = 10, Height = 360, Width = 480;
static const int startAngle = 0, spanAngle = 16 * 360;
// class toạ độ
class coordinate {
public:
    int x, y;
    coordinate(int, int);
    coordinate(const coordinate&);
    coordinate& operator=(const coordinate&);
};
// class người chơi
class player{
private:
    QString playerName;
    int playerScore;
public:
    player(QString,int);
    player(const player&);
    QString printInfo() const;
    bool operator<(player);
    int getScore() const;
    QString getName() const;
};
// enum chứa các hướng đi của rắn
enum directionEnumrate {
    right,
    up,
    left,
    down
};

// hàm tạo số nguyên ngẫu nhiên trong khoảng cho trước
int randomNumber(int, int);
// hàm so sánh 2 toạ độ
inline bool isSameCoordinate(coordinate c1, coordinate c2)
{
    return (c1.x == c2.x) && (c1.y == c2.y);
}
// hàm xử lý dòng text
void processLine(QString, QString&, int&);
#endif // FUNCTION_H
