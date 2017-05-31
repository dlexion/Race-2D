#include "finishwindow.h"
#include"game.h"

FinishWindow::FinishWindow(Game *lbl)
    :QLabel(lbl)
{
    game=lbl;
    this->setFixedSize(800,600);//lbl->size()

    replay = new QPushButton("Replay", this);
    replay->setAutoDefault(true);
    replay->setFocus();
    replay->setGeometry(20,520,160,60);

    menu = new QPushButton("Menu", this);
    menu->setGeometry(610,520,85,60);
    menu->setAutoDefault(true);

    exit = new QPushButton("Exit", this);
    exit->setGeometry(705,520,85,60);
    exit->setAutoDefault(true);

    connect(replay,SIGNAL(clicked(bool)),this,SLOT(slotClose()));
    connect(menu,SIGNAL(clicked(bool)),this,SLOT(slotMenu()));
    connect(exit,SIGNAL(clicked(bool)),lbl, SLOT(close()));

    hst = new HighscoreTable[6];
    read();
    addRecord();
    sort();
    save();

    this->show();

}

void FinishWindow::slotMenu()
{
    StartWindow* sw= new StartWindow;
    game->close();
}

void FinishWindow::slotClose()
{
    this->deleteLater();
    game->replay();
}

void FinishWindow::read()
{
    QString str;
    QFile file("table.txt");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        for(int i=0;i<5; i++)
        {

            stream >> hst[i].nick;
            stream >> str;
            hst[i].score=str.toInt();
        }
    }
    file.close();
}

void FinishWindow::save()
{
    QFile file("table.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream stream(&file);
        for(int i=0;i<5;i++)
        {
            if(!hst[i].nick.isEmpty()){
                stream << hst[i].nick;
                stream<<' ';
                stream << QString::number(hst[i].score);
                stream <<"\r\n";
            }
        }
    }
    file.close();
}

void FinishWindow::addRecord()
{
    hst[5].nick=game->getNick();
    hst[5].score=game->getScore();
}

void FinishWindow::sort()
{
    HighscoreTable tmp;
    for(int i=5;i>0;i--)
    {
        if(hst[i].score>hst[i-1].score || hst[i-1].nick.isEmpty())
        {
            tmp = hst[i];
            hst[i]=hst[i-1];
            hst[i-1]=tmp;
        }
        else
            break;
    }
}

void FinishWindow::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    paint.setFont(QFont("Times",20,QFont::Normal));
    paint.drawText(320,22,"Game over!");
    paint.drawText(300, 90, "Highscore table");
    paint.setFont(QFont("Times",15,QFont::Normal));
    paint.drawText(202,40,"Player: " + game->getNick());//
    paint.drawText(202,60, "Score: " + QString::number(game->getScore()-1));
    int y = 110;
    for(int i=0;i<5;i++)
    {
        if(!hst[i].nick.isEmpty()){
            //break;
            paint.drawText(202,y,QString::number(i+1) + ". "+ hst[i].nick);
            paint.drawText(402,y,QString::number(hst[i].score));
            y+=20;
        }
    }
}

FinishWindow::~FinishWindow()
{
    delete[] replay;
    delete[] menu;
    delete[] exit;
    delete[] hst;
}
