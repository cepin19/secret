#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <thread>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <map>
#ifndef CARD_H
#define CARD_H

using namespace std;
class Pile;
const vector <string> suitnames={"clubs", "diamonds", "hearts", "spades"};
const vector <string> ranknames={"ace", "2", "3", "4","5","6","7","8","9","10","jack","queen","king"};

enum Suits {clubs, diamonds, hearts, spades};
enum Rank {ace,two,three,four,five,six,seven,eight,nine,ten,jack,queen,king};

//vector <string> re={"🂡","🂢","🂣","🂤","🂥","🂦","🂧","🂨","🂩","🂪","🂫","🂬","🂭","🂮"};
extern  map <Suits,  vector <string> > faces;/*={{spades,{"🂡 ","🂢 ","🂣 ","🂤 ","🂥 ","🂦 ","🂧 ","🂨 " ,"🂩 ","🂪 ","🂫 ","🂬 ","🂭 ","🂮 "}}, \
    {clubs,{"🃑","🃒","🃓","🃔","🃕","🃖","🃗","🃘","🃙","🃚","🃛","🃜","🃝","🃞"}}, \
    {diamonds,{"🃁","🃂","🃃","🃄","🃅","🃆","🃇","🃈","🃉","🃊","🃋","🃌","🃍","🃎"}}, \
    {hearts,{"🂱","🂲","🂳","🂴","🂵","🂶","🂷","🂸","🂹","🂺","🂻","🂼","🂽","🂾"}}};*/

class Card
{
public:
    Rank rank;
    Suits suit;
    bool faceUp=false;
    Card(Rank rank, Suits suit, Pile* pile);
    Card();
    Pile * pile;
    bool differentColorAs(Suits second_suit);
    bool differentColorAs(Card *c);
    friend std::ostream &operator<<( ostream &output, const Card &c){
        output << faces[c.suit][c.rank];
        return output;
}

};

#endif // CARD_H
