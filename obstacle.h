#ifndef OBSTACLE_H
#define OBSTACLE_H
#include<QLabel>
#include<QPixmap>
#include<QPoint>
#include"game.h"

class Obstacle:public QLabel
{
    Q_OBJECT
    friend class Game;
protected:
    QPixmap pix;
    QPoint pos;
    QSize size;
    bool working;
    void random_pos();
    void moveDown();
public:
    Obstacle();

protected slots:
    void setWorking();
};


#endif // OBSTACLE_H
