#include "obstacle.h"

Obstacle::Obstacle()
{
    working=false;
    pos.setX(200);
    pos.setY(-100);
    pix.load("pictures/Let.png");
    size=pix.size();
}

void Obstacle::random_pos()
{
    working=false;
    pos.setY(-100);
    int x=rand()%4*100+200;
    pos.setX(x);
}

void Obstacle::setWorking()
{
    working=true;
}

void Obstacle::moveDown()
{
    pos.setY(pos.y()+5);
}
