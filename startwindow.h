#ifndef STARTWINDOW_H
#define STARTWINDOW_H
#include<QWidget>
#include<QPushButton>
#include<QGridLayout>
#include<QPainter>
#include<QInputDialog>
#include<QLineEdit>
#include"game.h"


class StartWindow : public QWidget
{
    Q_OBJECT
public:
    StartWindow(QObject *parent = 0);
    ~StartWindow();

private:
    QPushButton* start;
    QPushButton* edit;
    QPushButton* exit;
    QGridLayout * qgl;
    QString nickname;
    void paintEvent(QPaintEvent *event);
    void readNick();
    void saveNick();

public slots:
    void slotStartGame();
    void slotEditName();
};

#endif // STARTWINDOW_H
