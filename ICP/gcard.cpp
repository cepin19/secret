#include "gcard.h"
#include <QtWidgets>

GCard::GCard(QWidget *parent, Card *card): QLabel(parent)
{
    this->card=card;
    if (card->faceUp==true){
        std::stringstream ss;
        ss <<":/" << ranknames.at(card->rank)<< "_" << suitnames.at(card->suit);
        setPixmap(QPixmap(ss.str().c_str()).scaled(100,100,Qt::KeepAspectRatio));
    }
    else {
        setPixmap(QPixmap(":back").scaled(100,100,Qt::KeepAspectRatio));

    }
    setAttribute(Qt::WA_DeleteOnClose);
    //    QPixmap  * pic = new QPixmap("/test.png");
    //  setPixmap((*pic).scaled(150,150,Qt::KeepAspectRatio));

}
void GCard::updatePixmap(){
    //qDebug()<<this->card->faceUp;
    if (this->card->faceUp==true){
        std::stringstream ss;
        ss <<":/" << ranknames.at(this->card->rank)<< "_" << suitnames.at(this->card->suit);
        setPixmap(QPixmap(ss.str().c_str()).scaled(100,100,Qt::KeepAspectRatio));
    }
    else {
        setPixmap(QPixmap(":back").scaled(100,100,Qt::KeepAspectRatio));

    }
}
