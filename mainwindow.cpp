#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setBaseSize(480, 360);
    setFixedSize(480, 360);
    setWindowTitle("Snake!");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::game()
{
    snakePointer = new snake();
    g = new gameEvent(snakePointer);
    g->init();
    g->show();
}
void MainWindow::showHighScore()
{
    QFile f("highScores.txt");
    f.open(QIODevice::ReadOnly);
    QString text = "High scores:\n";
    while (!f.atEnd()) {
        text += f.readLine();
        text += "\n";
    }
    f.close();
    QMessageBox msgb;
    msgb.setText(text);
    msgb.setStandardButtons(QMessageBox::Ok);
    msgb.exec();
}
void MainWindow::on_pushButton_clicked()
{
    game();
}

void MainWindow::on_pushButton_2_clicked()
{
    showHighScore();
}
