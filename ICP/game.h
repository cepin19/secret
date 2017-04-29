#ifndef GAME_H
#define GAME_H
#include "card.h"
#include "move.h"
#include "pile.h"
#include <algorithm>


class Game
{
public:
    vector <Move*> history;
    vector <Pile*> piles;
    vector <Pile*> foundations;
    Pile* deck;
    Pile* deckBuffer;

    vector <Move*> possible_moves;
    int  make_deck();
    int  undo();
    int  shuffle_deck() ;
    int  make_piles();
    int  make_foundations();
    int make_deck_pile();
    int  move(char type,short from_pile, short to_pile, short card_idx);
    /*vraci true, pokud je pohyb povoleny, jinak false*/
    int make_move(char type,short from_pile, short to_pile, short card_idx);
    int make_move(char type, Pile* to_pile, Card * card);

    void show_history();
    void show_table();
    void update_possible_moves();
    void print_possible_moves();
    Game();





};

#endif // GAME_H
