#include "pile.h"

Pile::Pile(char type)
{
    this->type=type;
}

bool Pile::canPlace(Card *c){
    return canPlace(c->suit,c->rank);
}
bool Pile::canPlace(Suits suit, Rank rank){
    if (type=='f'){
        if (cards.empty()) {
            if (rank==ace){
                return true;
            }
        }
        else {//na foundation uz jsou nejake karty
            if (suit==cards.back()->suit && rank-1==cards.back()->rank){
                return true;
            }
        }
    }
    if (type=='p'){
        if (cards.empty()){ //empty pile, king can be placed here
            if (rank==king){
                return true;
                // possible_moves.push_back(new Move('p',pile-piles.begin(), topile-piles.begin(),std::distance(begin((*pile)->cards), c.base()) - 1));


            }
        }
        else { //there are some cards on the pile

            if (cards.back()->differentColorAs(suit) && rank+1==cards.back()->rank) // different color and rank just below the card on the pile
            {
                return true;
                //possible_moves.push_back(new Move('p',pile-piles.begin(), topile-piles.begin(),std::distance(begin((*pile)->cards), c.base()) - 1));

            }

        }


    }
    return false;
}
