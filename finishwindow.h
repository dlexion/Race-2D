#ifndef FINISHWINDOW_H
#define FINISHWINDOW_H
#include<QLabel>
#include<QPushButton>
#include<QPainter>
#include"startwindow.h"
#include"game.h"
#include"highscoretable.h"
class Game;

class FinishWindow : public QLabel
{
    Q_OBJECT
public:
    FinishWindow(Game* lbl = 0);
    ~FinishWindow();
private:
    QPushButton* replay;
    QPushButton* menu;
    QPushButton* exit;
    QString nickname;
    Game * game;
    HighscoreTable* hst;
    void read();
    void save();
    void sort();
    void addRecord();
    void paintEvent(QPaintEvent *);
private slots:
    void slotMenu();
    void slotClose();
};

#endif // FINISHWINDOW_H
