#ifndef MOVE_H
#define MOVE_H
#include <iostream>
using namespace std;
class Move
{
public:

    char type;
    //f = pile to foundation
    //p = pile to pile
    //b = buffer to pile
    //d = deck to buffer
    //g = buffer to foundation
    //u = foundation to pile
    //r = reload deck from deckBuffer
    short from_pile;
    short to_pile;
    short card_idx;
    Move(char type,short from_pile, short to_pile, short card_idx);
    friend ostream &operator<<( ostream &output, const Move &m) {
        output << m.type << " " << m.from_pile << " " << m.to_pile << " " << m.card_idx;
        return output;
     }

};

#endif // MOVE_H
