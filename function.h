#ifndef FUNCTION_H
#define FUNCTION_H

#include <QTime>
#include <QRandomGenerator>

static const int dotSize = 10, Height = 360, Width = 480;
static const int startAngle = 0, spanAngle = 16 * 360;
class coordinate {
public:
    int x, y;
    coordinate(int, int);
    coordinate(const coordinate&);
    coordinate& operator=(const coordinate&);
};
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
enum directionEnumrate {
    right,
    up,
    left,
    down
};

int randomNumber(int, int);
inline bool isSameCoordinate(coordinate c1, coordinate c2)
{
    return (c1.x == c2.x) && (c1.y == c2.y);
}
void processLine(QString, QString&, int&);
#endif // FUNCTION_H
