#include "gpile.h"
#include <stdio.h>

GPile::GPile(QWidget *parent, Pile *pile): QLabel(parent)
{
    this->pile=pile;

    //setPixmap(QPixmap(":back").scaled(100,100,Qt::KeepAspectRatio));
    setStyleSheet("border-radius: 5px");
    setStyleSheet("border: 5px solid green");
    setFixedSize(68,100);
    this->show();

}

