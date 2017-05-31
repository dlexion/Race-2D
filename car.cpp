#include "car.h"

Car::Car()
{

    pos.setX(370);
    pos.setY(440);
    pix.load("pictures/Car3.png");
    size=pix.size();
}

void Car::slotMoveCar()
{
    if(GetAsyncKeyState(0x41) && pos.x()>=205){
        pos.setX(pos.x()-3);
    }
    if(GetAsyncKeyState(0x44) && pos.x()<=535){
        pos.setX(pos.x()+3);
    }
}
