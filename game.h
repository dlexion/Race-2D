#ifndef GAME_H
#define GAME_H
#include<QLabel>
#include<QKeyEvent>
#include<QTimer>
#include<ctime>
#include<Windows.h>
#include"finishwindow.h"

class Car;
class Obstacle;

class Game:public QLabel
{
    Q_OBJECT

public:
    Game(QString nick);
    ~Game();
    void replay();
    QString getNick();
    int getScore();

private:
    Car* car;
    Obstacle* obs;
    int number_obs;
    void paintEvent(QPaintEvent *event);
    QTimer tmr_move;
    QTimer tmr_speed;
    QTimer tmr_start;
    unsigned int speed;
    int score;

    bool lose;
    QString nickname;
    bool pause;
    void keyPressEvent(QKeyEvent *ev);

private slots:
    void slotSpeed();
    void slotMoveLet();
    void check();
    void slotStartWork();
    void slotChekImposition();
    void slotUpdateScore();
};

#endif // GAME_H
