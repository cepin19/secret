#include "card.h"

Card:: Card(Rank rank, Suits suit, Pile *pile){
    this->rank=rank;
    this->suit=suit;
    this->pile=pile;
}
Card::Card(){};

bool Card::differentColorAs(Card *c){
    if (suit==clubs or suit==spades){return (c->suit==hearts||c->suit==diamonds);}
    else {return (c->suit==clubs||c->suit==spades);}
}
bool Card::differentColorAs(Suits second_suit){
    if (suit==clubs or suit==spades){return (second_suit==hearts||second_suit==diamonds);}
    else {return (second_suit==clubs||second_suit==spades);}
}
//std::ostream Card::&operator<<( ostream &output, const Card &c)
