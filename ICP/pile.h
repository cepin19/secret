#ifndef PILE_H
#define PILE_H
#include <vector>
#include "card.h"
//class Card;

class Pile
{
public:
    std::vector <Card*> cards;
    Pile(char);
    char type;
    bool canPlace(Card *c);
    bool canPlace(Suits suit, Rank rank);
};

#endif // PILE_H
