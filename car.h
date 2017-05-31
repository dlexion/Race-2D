#ifndef CAR_H
#define CAR_H
#include<QLabel>
#include<QPixmap>
#include<QPoint>
#include"game.h"


class Car : public QLabel
{
    Q_OBJECT
    friend class Game;
protected:
    QPixmap pix;
    QPoint pos;
    QSize size;
public:
    Car();
public slots:
    void slotMoveCar();
};

#endif // CAR_H
