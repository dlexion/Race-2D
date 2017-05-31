#include "game.h"
#include"car.h"
#include"obstacle.h"

Game::Game(QString nick)
    :QLabel()
{
    this->setFixedSize(800,600);
    this->setWindowIcon(QIcon("pictures/Icon.png"));
    QPalette qp;
    qp.setBrush(this->backgroundRole(),QBrush(QPixmap("pictures/road.png")));
    this->setPalette(qp);
    this->setWindowTitle("Race 2D");
    car=new Car;
    number_obs=1;
    obs=new Obstacle[3];

    speed=30;
    tmr_move.start(1000/speed);
    tmr_speed.start(speed);
    tmr_start.start(1000);

    connect(&tmr_speed,SIGNAL(timeout()),this,SLOT(slotSpeed()));
    connect(&tmr_move,SIGNAL(timeout()),car,SLOT(slotMoveCar()));
    connect(&tmr_move,SIGNAL(timeout()),this,SLOT(slotChekImposition()));
    connect(&tmr_move,SIGNAL(timeout()),this,SLOT(slotMoveLet()));
    connect(&tmr_move,SIGNAL(timeout()),this,SLOT(check()));
    connect(&tmr_move,SIGNAL(timeout()),this,SLOT(slotUpdateScore()));
    connect(&tmr_move,SIGNAL(timeout()),this,SLOT(update()));
    connect(&tmr_start,SIGNAL(timeout()),this,SLOT(slotStartWork()));

    score=0;
    lose=false;
    nickname=nick;
    pause=false;
    this->show();
}

void Game::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);

    paint.drawPixmap(car->pos,car->pix);
    for(int i=0;i<number_obs;i++)
    {
        if(obs[i].working)
            paint.drawPixmap(obs[i].pos,obs->pix);
    }

    if(!lose) {
        paint.setFont(QFont("Times",15,QFont::Normal));
        paint.drawText(630,580,"Speed: " + QString::number(speed) + " Km/h");
        paint.drawText(10,20, "Score: " + QString::number(score));
    }

    if(pause){
        paint.setFont(QFont("Times",60,QFont::Normal));
        paint.drawText(290,100,"PAUSE");
    }
}


void Game::slotSpeed()
{
    if(GetAsyncKeyState(87) && speed<100){
        speed++;
        tmr_speed.start(speed*3);
        tmr_move.start(1000/speed);
    }
    if(GetAsyncKeyState(83) && speed>30){
        speed--;
        tmr_speed.start(60);
        tmr_move.start(1000/speed);
    }
}

void Game::slotMoveLet()
{
    for(int i=0;i<number_obs;i++)
    {
        if(obs[i].pos.y()>600)
        {
            obs[i].working=false;
            score+=50;
            obs[i].random_pos();
        }
        if(obs[i].working)
        {
            obs[i].moveDown();
        }

    }

}

void Game::check()
{
    int cxl = car->pos.x();//left
    int cxr = cxl+car->size.width();//right
    int cyt = car->pos.y();//top
    int cyb = cyt+car->size.height();//bottom
    for(int i=0;i<number_obs;i++)
    {
        if(obs[i].working)
        {
            int oxl=obs[i].pos.x();
            int oxr = oxl + obs->size.width();
            int oyt=obs[i].pos.y();
            int oyb = oyt + obs->size.height();
            if((cxl<oxr && cxr>oxl)
                    &&(oyb>cyt && oyt<cyb)){
                qDebug() <<"LOSE!";
                tmr_move.stop();
                tmr_speed.stop();
                lose=true;
                update();
                FinishWindow* fw = new FinishWindow(this);
            }
        }
    }
}

void Game::slotStartWork()
{
    int j=0;
    while(j<number_obs)
    {

        if(!obs[j].working)
        {
            int interval = rand()%1000;
            obs[j].random_pos();
            QTimer::singleShot(interval,&obs[j], SLOT(setWorking()));

        }
        j++;
    }
}

void Game::slotChekImposition()
{
    for(int i=0;i<number_obs;i++)
    {
        for(int j=0;j<number_obs;j++)
        {
            if(i!=j && obs[i].pos.x()==obs[j].pos.x() && obs[i].working && obs[j].working)
            {
                if(obs[i].pos.y()<obs[j].pos.y() && obs[i].pos.y()+100>obs[j].pos.y())//obs[i].pos.y()<obs[j].pos.y()+100 && obs[i].pos.y()+100>obs[j].pos.y()
                {
                    obs[i].pos.setY(obs[j].pos.y()-100);
                }
            }
        }
    }
}

void Game::slotUpdateScore()
{
    score++;
    if(score>=1000 && score <1050)
    {
        qDebug()<<"ADD";
        number_obs=2;
    }
    if(score>=3000 && score <=3100)
    {
        qDebug()<<"ADD+";
        number_obs=3;
    }

}

void Game::replay()
{
    number_obs=1;
    speed=30;
    score=0;
    lose=false;
    pause=false;
    car->pos.setX(370);
    for(int i=0;i<3;i++){
        obs[i].random_pos();
    }
    tmr_move.start(1000/speed);
    tmr_speed.start(speed);

}

QString Game::getNick()
{
    return nickname;
}

int Game::getScore()
{
    return score;
}

Game::~Game()
{
    delete[] car;
    delete[] obs;
}

void Game::keyPressEvent(QKeyEvent *ev)
{
    int key=ev->key();
    if(key==Qt::Key_Escape){
        if(!pause){
            pause=true;
            tmr_move.stop();
            tmr_speed.stop();
            tmr_start.stop();
            update();
        }
        else
        {
            pause=false;
            tmr_move.start(1000/speed);
            tmr_speed.start(speed*3);
            tmr_start.start(1000);
        }
    }
}
