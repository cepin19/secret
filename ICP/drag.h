#ifndef DRAG_H
#define DRAG_H
#include<QFrame>
#include<QWidget>
#include "gcard.h"
#include <QPushButton>
#include <QApplication>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include <QFrame>
#include <iostream>
#include <QPainter>
#include "gpile.h"
#include "game.h"
class DragWidget : public QFrame
{
public:
    DragWidget(QWidget *parent = 0);
    Card * pickedCard;
    Game * g;
    vector <GPile *>gpiles; //neni potreba
    vector <GCard *>gcards; //taky ne
    vector <GCard *>GDeckBuffer;

protected:
   void dragEnterEvent(QDragEnterEvent *event) override;
   void dragMoveEvent(QDragMoveEvent *event) override;
   void dropEvent(QDropEvent *event) override;
   void mousePressEvent(QMouseEvent *event) override;
private:
   void reloadCards();
};



#endif // DRAG_H
