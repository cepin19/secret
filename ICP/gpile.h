#ifndef GPILE_H
#define GPILE_H

#include <QObject>
#include <QLabel>
#include <iostream>

#include "pile.h"
#include "gcard.h"

class GPile : public QLabel
{
public:
    GPile(QWidget *parent = 0,Pile* pile=0);

    Pile * pile;
    bool deck;
    bool foundation;
    GCard * gcards;

};

#endif // GPILE_H
