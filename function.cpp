#include "function.h"

coordinate::coordinate(int a, int b)
{
    x = a;
    y = b;
}
coordinate::coordinate(const coordinate& c)
{
    this->x = c.x;
    this->y = c.y;
}
coordinate& coordinate::operator=(const coordinate& c)
{
    this->x = c.x;
    this->y = c.y;
    return *this;
}

player::player(QString name, int score)
{
    this->playerName = name;
    this->playerScore = score;
}
player::player(const player& p)
{
    this->playerName = p.getName();
    this->playerScore = p.getScore();
}
int player::getScore() const
{
    return this->playerScore;
}
QString player::getName() const
{
    return this->playerName;
}
QString player::printInfo() const
{
    return this->playerName + "\t" + QString::number(this->playerScore);
}
bool player::operator<(player p)
{
    return this->playerScore < p.getScore() ? true : false;
}
int randomNumber(int a, int b)
{
    QTime time = QTime::currentTime();
    QRandomGenerator qrand(time.msec());
    return a + qrand.generate() % (b - a + 1);
}
void processLine(QString line, QString& key, int& value)
{
    int seperatePosition = line.indexOf('\t');
    key = line.sliced(0, seperatePosition);
    value = line.sliced(seperatePosition + 1).toInt();
}

