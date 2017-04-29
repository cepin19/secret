#include "move.h"

Move::Move(char type,short from_pile, short to_pile, short card_idx) {
    this->type=type;
    this->from_pile=from_pile;
    this->to_pile=to_pile;
    this->card_idx=card_idx;
}

