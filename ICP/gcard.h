#ifndef GCARD_H
#define GCARD_H
#include "card.h"
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QLabel>


/*
class Card : public QGraphicsPixmapItem
{
public:
    Card();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QPixmap pic;
};
*/

class GCard : public QLabel
{
public:
    Card *card;
   GCard(QWidget *parent = 0, Card *card=0);
    void updatePixmap();
protected:
   // void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
   // void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
   // void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QPixmap pic;
};

#endif // GCARD_H
