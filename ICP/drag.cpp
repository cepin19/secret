#include "drag.h"
#include <QWidget>
#include <QDebug>
#include <QFrame>

DragWidget::DragWidget(QWidget *parent)
    : QFrame(parent)
{
    // setFixedSize(200, 200);
    //  setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);

    /*QLabel *boatIcon = new QLabel(this);
    boatIcon->setPixmap(QPixmap("/test.png"));
    boatIcon->move(10, 10);
    boatIcon->show();
    boatIcon->setAttribute(Qt::WA_DeleteOnClose);
*/
    g=new Game();

    for (auto it=g->piles.begin();it<g->piles.end();++it) {
        GPile *p = new GPile(this,*it);
        //gpiles.push_back(p);
        p->move(20+(it - g->piles.begin())*100, 150);
        for (auto cit=p->pile->cards.begin();cit<p->pile->cards.end();++cit) {
            /*for (auto cit=p->pile->cards.begin();cit<p->pile->cards.end();++cit) {*/

            GCard *c = new GCard(this,(*cit));
            gcards.push_back(c);
            if ((*cit)==p->pile->cards.back()){
                /* std::stringstream ss;
                ss <<":/" << ranknames.at(c->card->rank)<< "_" << suitnames.at(c->card->suit);
                c->setPixmap(QPixmap(ss.str().c_str()).scaled(100,100,Qt::KeepAspectRatio));
                */}
            else {
                // c->setPixmap(QPixmap(":back").scaled(100,100,Qt::KeepAspectRatio));
            }
            c->move(20+(it - g->piles.begin())*100,150+(cit - p->pile->cards.begin())*5);
        }

        p->show();


    }
    g->update_possible_moves();
    GPile *dck = new GPile(this,g->deck);
    dck->move(20, 20);
    dck->show();
    GPile *deckBuffer = new GPile(this,g->deckBuffer);
    deckBuffer->move(120, 20);
    deckBuffer->show();

    for (auto it=g->deck->cards.begin();it<g->deck->cards.end();++it) {
        qDebug() << (*it)->rank << (*it)->suit;

        GCard *b = new GCard(this,*it);
        std::stringstream ss;
        ss <<":/" << ranknames.at(b->card->rank)<< "_" << suitnames.at(b->card->suit);
        qDebug()<< ss.str().c_str();
        //b->setPixmap(QPixmap(ss.str().c_str()).scaled(100,100,Qt::KeepAspectRatio));
        b->move(20, 20);
        b->show();
        gcards.push_back(b);

        b->setAttribute(Qt::WA_DeleteOnClose);
    }


    for (auto it=g->foundations.begin();it<g->foundations.end();++it) {
        GPile *p = new GPile(this,*it);
        p->move(320+(it - g->foundations.begin())*100, 20);
        p->pile->type='f';
        p->show();
    }

    /*   GCard *houseIcon = new GCard(this);
    houseIcon->move(10, 80);
    houseIcon->show();
    houseIcon->setAttribute(Qt::WA_DeleteOnClose);

   GCard *c = new GCard(this);
    c->move(0, 0);
    c->show();
    c->setAttribute(Qt::WA_DeleteOnClose);*/
}

void DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            //event->acceptProposedAction();
            //this->rank=card->rank;
            //this->suit=card->suit;
        }
    } else {
        event->ignore();
    }
}
void DragWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}


void DragWidget::reloadCards()
{

    QList<QLabel *> myCards=findChildren<QLabel*>();
    //  qDebug()<<myCards.size();

    for (auto it=myCards.begin();it<myCards.end();++it){
        GCard * gc = dynamic_cast<GCard *>(*it);

        if (gc){
            //qDebug()<<gc->card->rank<<endl;

            gc->updatePixmap();
            if (gc->card->pile->type=='d'){//after deck reload
                //gc->move();
                qDebug()<<"moving";
                gc->move(20, 20);
                gc->show();
            }
        }
    }
}

void DragWidget::dropEvent(QDropEvent *event)
{
    GPile * gpile = dynamic_cast<GPile *>(childAt(event->pos()));
    GCard * gcard = dynamic_cast<GCard *>(childAt(event->pos()));

    if (!gpile && !gcard  ){return;}
    if (gcard && (gcard->card==this->pickedCard)) return;
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        //qDebug()<< g->piles.front()->cards.front()->rank;
        Pile * toPile;
        char type;

        if (gcard){

            for (auto p=g->piles.begin();p<g->piles.end();  ++p)
            {
                for (auto c=(*p)->cards.begin();c<(*p)->cards.end();c++){
                    if (*c==gcard->card){ //su ve spravnem balicku
                        toPile=(*p);
                        break;
                    }
                }
            }

            for (auto f=g->foundations.begin();f<g->foundations.end();  ++f)
            {
                for (auto c=(*f)->cards.begin();c<(*f)->cards.end();c++){
                    if (*c==gcard->card){ //su ve spravnem balicku
                        toPile=(*f);
                        break;
                    }
                }
            }
        }
        else { //gpile
            for (auto p=g->piles.begin();p<g->piles.end();  ++p){
                if (*p==gpile->pile) {
                    toPile=(*p);
                    break;
                }
            }
            for (auto f=g->foundations.begin();f<g->foundations.end();  ++f)
                if (*f==gpile->pile){ //su ve spravnem balicku
                    toPile=(*f);
                    break;
                }
        }



        dataStream >> pixmap >> offset ;
        qDebug()<<"toPile type: "<<toPile->type;
        if (toPile->type=='f' && this->pickedCard->pile->type=='p'){ //pile to foundation
            if (!g->make_move('f',toPile,this->pickedCard)) return ;

        }
        else if (toPile->type=='p' && this->pickedCard->pile->type=='p') { //pile to pile
            if (!g->make_move('p',toPile,this->pickedCard)) return ;

        }
        else if (toPile->type=='p' && this->pickedCard->pile->type=='b') { //buffer to pile
            if (!g->make_move('b',toPile,this->pickedCard)) return ;
        }
        else if (toPile->type=='f' && this->pickedCard->pile->type=='b') { //buffer to foundation
            if (!g->make_move('g',toPile,this->pickedCard)) return ;
        }
        else if (toPile->type=='p' && this->pickedCard->pile->type=='f') { //foundation to pile
            if (!g->make_move('u',toPile,this->pickedCard)) return ;
        }
        reloadCards();

        GCard *newCard = new GCard(this,(this->pickedCard));
        //newCard->setPixmap(pixmap);
        if (gpile) {
            newCard->move(gpile->x(),gpile->y());
        }
        else if (gcard){
            if (toPile->type=='f'){
                newCard->move(gcard->x(),gcard->y());
            }


            else
            {
                newCard->move(gcard->x(),gcard->y()+15);
            }

        }
        newCard->show();
        newCard->setAttribute(Qt::WA_DeleteOnClose);
        g->show_table();

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

//! [1]
void DragWidget::mousePressEvent(QMouseEvent *event)
{
    GCard *child = dynamic_cast<GCard*>(childAt(event->pos()));
    if (!child) {//pokud klikam na prazdny pile misto na kartu
        GPile *pile = dynamic_cast<GPile*>(childAt(event->pos()));
        if (pile && pile->pile->type=='d'){ //reload deck
            qDebug()<<"empty";

            g->make_move('r',0,0,0);
            reloadCards();
            return;
        }
        else return;
    }
    Card* c = child->card;
    qDebug()<<c->pile->type << c->rank;
    if (c->pile->type=='d'){ //deck
        qDebug()<<"asd";
        g->make_move('d',g->deckBuffer,c);
        // child->move(120+(float(rand())/INT_MAX)*100,20);
        child->move(120,20);

        /*for (auto it=GDeckBuffer.rbegin();it<GDeckBuffer.rend();++it){
            (*it)->move(120,20);

            (*it)->show();

            }*/
        child->raise();
        child->show();
        GDeckBuffer.push_back(child);
        reloadCards();
        return;
    }
    this->pickedCard=c;
    //qDebug()<<c->rank;
    QPixmap pixmap = *child->pixmap();
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());
    //! [1]

    //! [2]
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);
    //! [2]

    //! [3]
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());
    //! [3]



    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}
