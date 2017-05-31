#ifndef HIGHSCORETABLE_H
#define HIGHSCORETABLE_H
#include<QString>
#include<QFile>
#include<QTextStream>
#include<QtDebug>

struct HighscoreTable
{
public:
    HighscoreTable();
    QString nick;
    int score;
};

#endif // HIGHSCORETABLE_H
