#include <stdio.h>
#include <thread>
#include <vector>
#include <string>
#include <iostream> 
#include <algorithm> 


using namespace std;
class Card{
	public:
	short value;
	short color;
	bool faceUp;
	Card(short value,short color){
		this->value=value;
		this->color=color;
		}
	//simlarColorTo(Card)
	
	};

typedef Pile vector <Card*> cards;
//class Pile{
	//public:
	//;};
class Move{
	public:
	char type;
	short from_pile;
	short to_pile;
	short card_idx;

	Move(char type,short from_pile, short to_pile, short card_idx) {
		this->type=type;
		this->from_pile=from_pile;
		this->to_pile=to_pile;}
	};

class Game{
	public:
	vector <Move*> history;
	vector <Pile*> piles;
	vector <Pile*> foundations;
	vector <Card*> deck;
	vector <Move*> possible_moves;
	int make_deck(){
		for (short t=0;t!=4;t++){
			for (short v=0;v!=13;v++) {
				Card *c=new Card(v,t);
				deck.push_back(c);
				}
			}
		return 0;
		}
	int undo(){
		Move * last_move=history.back(); 
		cout <<"UNDO " << last_move->type << " " << last_move->from_pile << " " << last_move->to_pile << endl; 
		Card *c;
		switch(last_move->type){
			case 'f':
				c=foundations.at(last_move->to_pile)->cards.back(); //get the card
				cout << "returning the card ("<< c->value  << "-" << c->color << ") back from foundation number "<<last_move->to_pile<<" to pile numer " << last_move->from_pile << endl;
				foundations.at(last_move->to_pile)->cards.pop_back(); //remove it from foundatoin
				piles.at(last_move->from_pile)->cards.push_back(c);//return it to the original pile
				break;
			case 'd':
				c=piles.at(last_move->to_pile)->cards.back(); //get the card
				cout << "returning the card ("<< c->value  << "-" << c->color << ") back from pile number "<<last_move->to_pile<<" to top of the deck"<< endl;
				piles.at(last_move->to_pile)->cards.pop_back(); //remove it from pile
				deck.push_back(c);//return it to the deck
				break;
			} 
			
		history.pop_back();
		return 0;
		}
	int shuffle_deck() {
		random_shuffle ( deck.begin(), deck.end() );
		return 0;}	

	int make_piles(){
		for (int i=0;i!=7;i++){
			Pile *p=new Pile();
			for (int x=0;x!=i+1;x++){
				p->cards.push_back(deck.back());
				deck.pop_back();
				}
			piles.push_back(p);
			}
			return 0;
			}	
			
	int make_foundations(){
		for (int i=0;i!=4;i++){
			Pile *p=new Pile();
			foundations.push_back(p);
			}
			return 0;
			}
	
	int move(char type,short from_pile, short to_pile){
		Move *m=new Move(type,from_pile, to_pile);
		history.push_back(m);
		Card * c;
		switch (type) {
			case 'f': //pile to foundation
				c=piles.at(from_pile)->cards.back();
				foundations.at(to_pile)->cards.push_back(c);
				piles.at(from_pile)->cards.pop_back();
				break;
			case 'd': //from deck to pile, from_pile parameter unused
				c=deck.back();
				piles.at(to_pile)->cards.push_back(c);
				deck.pop_back();
				break;

			}
		return 0;
		}
	int make_move(char type,short from_pile, short to_pile)
	{
		//check if legal, i.e. if the move is in the set of possible moves
		bool legal=true;
		if (!legal) {
			return false;
			}
		move(type,from_pile, to_pile);
		return 0;
	}

	void show_history(){
		for (auto it=history.begin();it<history.end();it++) {
			cout << (*it)->type << " " << (*it)->from_pile << " " << (*it)->to_pile << endl; 
		}
	}
	void show_table(){	
		cout << "Deck:" << endl;
		for (auto it=deck.begin();it<deck.end();it++) {
			cout<<(*it)->value<<"-"<<(*it)->color<<",";}
		cout<<endl;
		
		cout << "Piles:" << endl;
		for (auto i=piles.begin();i<piles.end();i++) {
				for (auto c=(*i)->cards.begin();c<(*i)->cards.end();c++) {
				cout<<(*c)->value <<"-"<<(*c)->color<<endl;}
			cout<<endl;} 
		
		cout << "Foundations:" << endl;
		for (auto i=foundations.begin();i<foundations.end();i++) {
				for (auto c=(*i)->cards.begin();c<(*i)->cards.end();c++) {
				cout<<(*c)->value<<"-"<<(*c)->color<< endl;}
			cout<<endl;} 
		
		}		
	//updates the set of possible moves, used for legality check and hints for user
	void update_possible_moves(){
		return;}
	
	Game(){
		make_deck();
		srand(unsigned(std::time(0)));
		shuffle_deck();
		make_piles();
		make_foundations();
		}
	};

	
int main(){
	Game g=Game();

	//generate deck
	g.show_table();	
	g.make_move('f',0,0);
	g.make_move('f',2,0);
	g.make_move('f',2,1);
	g.make_move('f',6,1);
	//g.make_move('f',16,1);

	g.make_move('d',0,1);

	g.show_table();	
	g.show_history();
	g.undo();
	g.undo();
	g.show_table();	
	g.show_history();
} 
