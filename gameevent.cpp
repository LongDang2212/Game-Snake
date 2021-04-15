#include "gameevent.h"

gameEvent::gameEvent(snake* ptr)
{
    snakePtr = ptr;
    connect(timer1, SIGNAL(timeout()), this, SLOT(loop()));
    setStyleSheet("background-color:#292828;");
    setWindowTitle("Snake!");
    resize(Width, Height);
    setBaseSize(Width, Height);
    setFixedSize(Width, Height);
}

int gameEvent::getScore()
{
    return score;
}
void gameEvent::setScore(int s)
{
    score = s;
}
void gameEvent::saveHighScore(QString playerName)
{
    QFile f(savedGamePath);
    f.open(QIODevice::ReadOnly);
    QString line;
    QVector<player> v;
    v.push_back(player(playerName, score));
    while (!f.atEnd()) {
        line = f.readLine();
        QString key;
        int value;
        processLine(line, key, value);
        v.push_back(player(key, value));
    }
    f.close();
    std::sort(v.begin(), v.end());
    std::reverse(v.begin(), v.end());
    f.open(QIODevice::ReadWrite | QIODevice::Truncate);
    for (int i = 0; i < 5; i++) {
        f.write((v.at(i).printInfo() + "\n").toUtf8());
    }
    f.close();
}
void gameEvent::localeFood()
{
    coordinate temp1(0, 0); // biến tạm, chứa vị trí mồi mới
    bool flag1 = false; // đặt 1 cờ, thể hiện sự hợp lệ của vị trí mồi
    do {
        // đặt mồi ở vị trí ngẫu nhiên
        temp1 = coordinate(randomNumber(1, int(Width / 10) - 1) * 10, randomNumber(1, int(Height / 10) - 1) * 10);
        flag1 = true;   // thay đổi cờ thành đúng
        QVector<coordinate> temp2 = snakePtr->getSnakeCoordinateVector();
        // kiểm tra xem nếu mồi trùng với rắn thì đặt cờ là sai
#pragma omp parallel for
        for (int i = 0; i < temp2.size(); i++) {
            if (isSameCoordinate(temp1, temp2.at(i))) {
                flag1 = false;
            }
        }
    } while (!flag1);   // vòng lặp sẽ chạy đến khi cờ đúng, vị trí mồi hợp lệ
    this->foodCoordinate = temp1;   // cập nhật vị trí mồi
}
void gameEvent::eat()
{
    // nếu cờ phần thưởng đúng thì +50 điểm, sai thì +10
    if (isGift) {
        score += 50;
    }
    else {
        score += 10;
    }
    snakePtr->eat();    // rắn ăn mồi, dài ra
    // xác định cờ phần thưởng, cứ 5 lần ăn mồi thường sẽ có thưởng
    isGift = ((snakePtr->getSnakeCoordinateVector().size() - 3) % 5 == 0) ? true : false;
    localeFood();
}
void gameEvent::keyPressEvent(QKeyEvent* e)
{
    int key = e->key();
    if ((key == Qt::Key_Left) || (key == Qt::Key_A)) {
        direction = left;
    }
    else if ((key == Qt::Key_Right) || (key == Qt::Key_D)) {
        direction = right;
    }
    else if ((key == Qt::Key_Up) || (key == Qt::Key_W)) {
        direction = up;
    }
    else if ((key == Qt::Key_Down) || (key == Qt::Key_S)) {
        direction = down;
    }
    else if (key == Qt::Key_Space) {
        pause = !pause;
    }
}
void gameEvent::paintEvent(QPaintEvent*)
{
    QPainter qp(this);
    qp.setRenderHint(QPainter::Antialiasing);
    if (inGame) {
        //draw snake
        QVector<coordinate> temp = snakePtr->getSnakeCoordinateVector();

        qp.setBrush(QBrush("#1ac500"));
        for (int i = 1; i < temp.size(); i++) {
            qp.drawChord(temp.at(i).x, temp.at(i).y, dotSize, dotSize, startAngle, spanAngle);
        }

        qp.setBrush(QBrush("#c50024"));
        qp.drawChord(temp.first().x, temp.first().y, dotSize, dotSize, startAngle, spanAngle);
        //draw food
        qp.setBrush(QBrush("yellow"));
        if (isGift) {
            qp.setBrush(QBrush("#f2f2f7"));
            qp.drawChord(foodCoordinate.x, foodCoordinate.y, dotSize, dotSize, startAngle, spanAngle);
        }
        else {
            qp.drawChord(foodCoordinate.x, foodCoordinate.y, dotSize, dotSize, startAngle, spanAngle);
        }
    }

    else {
        setStyleSheet("background-color:#42f2f5;");
        QString message = "Game over!\nYour score:" + QString::number(score);
        QFont font("Courier", 15, QFont::DemiBold);
        qp.setFont(font);
        qp.setPen(QPen(QBrush("#0d0d0d"), 1));
        qp.drawText(rect(), Qt::AlignCenter, message);
    }
}
void gameEvent::move()
{
    snakePtr->move();
}
void gameEvent::checkCollision()
{
    QVector<coordinate> temp = snakePtr->getSnakeCoordinateVector();
// kiểm tra xem rắn có tự cắn mình
#pragma omp parallel for
    for (int i = 1; i < temp.size(); i++) {

        if (isSameCoordinate(temp.at(0), temp.at(i))) {
            inGame = false;
        }
    }
// kiểm tra nếu rắn đi xuyên tường
#pragma omp parallel
{
    if (temp.at(0).x >= Width) {
        snakePtr->setHeadCoordinate(coordinate(0, temp.at(0).y));
    }

    if (temp.at(0).y >= Height) {
        snakePtr->setHeadCoordinate(coordinate(temp.at(0).x, 0));
    }

    if (temp.at(0).x < 0) {
        snakePtr->setHeadCoordinate(coordinate(Width, temp.at(0).y));
    }

    if (temp.at(0).y < 0) {
        snakePtr->setHeadCoordinate(coordinate(temp.at(0).x, Height));
    }
}
    // kiểm tra xem rắn có ăn mồi
    if (isSameCoordinate(temp.at(0), foodCoordinate)) {
        this->eat();
    }
}
void gameEvent::loop()
{
    // cờ pause thể hiện game có tạm dừng hay không
    // cờ inGame thể hiện game vẫn diễn ra hay đã kết thúc
    if (!pause) {
        if (inGame) {

            snakePtr->setDirection(direction);

            move();
            checkCollision();
            // hàm update sẽ cập nhật đồ hoạ
            update();
        }
        else {  // nếu game đã kết thúc
            if (flag) { // cờ flag dùng để xác định trạng thái tên người chơi
                QString name = getPlayerName();
                saveHighScore(name);
            }
            flag = false;
            this->~gameEvent();
        }
    }
}
void gameEvent::init()
{
    inGame = true;
    score = 0;
    localeFood();
    timer1->start(SPEED);
}
QString gameEvent::getPlayerName()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Player name"),
        tr("Enter your name:"), QLineEdit::Normal,
        QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
        return text;
}
