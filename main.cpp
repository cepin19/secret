#include <stdio.h>
#include <thread>
#include <vector>
#include <string>
#include <iostream> 
#include <algorithm> 
#include <sstream> 

enum Suits {clubs, diamonds, hearts, spades};
enum Rank {ace,two,three,four,five,six,seven,eight,nine,ten,jack,queen,king};
using namespace std;
class Card{
	public:
	Rank rank;
	Suits suit;
	bool faceUp;
	Card(Rank rank, Suits suit){
		this->rank=rank;
		this->suit=suit;
		}
	bool differentColorAs(Card *c){
		if (suit==clubs or suit==spades){return (c->suit==hearts||c->suit==diamonds);}
		else {return (c->suit==clubs||c->suit==spades);}
		}
	
	};

//typedef Pile vector <Card*> cards;
class Pile{
	public:
	vector <Card*> cards;
	;};
class Move{
	public:
	char type;
	short from_pile;
	short to_pile;
	short card_idx;

	Move(char type,short from_pile, short to_pile, short card_idx) {
		this->type=type;
		this->from_pile=from_pile;
		this->to_pile=to_pile;
		this->card_idx=card_idx;
	}
    friend ostream &operator<<( ostream &output, const Move &m) { 
         output << m.type << " " << m.from_pile << " " << m.to_pile << " " << m.card_idx;
         return output;             
      }
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
				Card *c=new Card((Rank) v,(Suits) t);
				deck.push_back(c);
				}
			}
		return 0;
		}
	int undo(){
		if (history.empty()){return -1;}
		Move * last_move=history.back(); 
		cout <<"UNDO " << last_move->type << " " << last_move->from_pile << " " << last_move->to_pile << endl; 
		Card *c;
		switch(last_move->type){
			case 'f':
				c=foundations.at(last_move->to_pile)->cards.back(); //get the card
				cout << "returning the card ("<< c->rank  << "-" << c->suit << ") back from foundation number "<<last_move->to_pile<<" to pile numer " << last_move->from_pile << endl;
				foundations.at(last_move->to_pile)->cards.pop_back(); //remove it from foundatoin
				piles.at(last_move->from_pile)->cards.push_back(c);//return it to the original pile
				break;
			case 'd':
				c=piles.at(last_move->to_pile)->cards.back(); //get the card
				cout << "returning the card ("<< c->rank  << "-" << c->suit << ") back from pile number "<<last_move->to_pile<<" to top of the deck"<< endl;
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
	
	int move(char type,short from_pile, short to_pile, short card_idx){
		Move *m=new Move(type,from_pile, to_pile,card_idx);
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
	int make_move(char type,short from_pile, short to_pile, short card_idx)
	{
		//check if legal, i.e. if the move is in the set of possible moves
		bool legal=true;
		if (!legal) {
			return false;
			}
		move(type,from_pile, to_pile,card_idx);
		return 0;
	}
	void show_history(){
		for (auto it=history.begin();it<history.end();it++) {
			cout << (*it)->type << " " << (*it)->from_pile << " " << (*it)->to_pile << endl; 
		}
	}
	void show_table(){	
		cout << "Deck:" << endl;
		for (auto it=deck.begin();it<deck.end();++it) {
			cout<<(*it)->rank<<"-"<<(*it)->suit<<",";}
		cout<<endl;
		
		cout << "Piles:" << endl;
		for (auto i=piles.begin();i<piles.end();++i) {
				//if ((*i)->cards.empty()){ cout << "empty";continue;}
				for (auto c=(*i)->cards.begin();c<(*i)->cards.end();c++) {
				cout<<(*c)->rank <<"-"<<(*c)->suit<<endl;}
			cout<<endl;} 
		
		cout << "Foundations:" << endl;
		for (auto i=foundations.begin();i<foundations.end();i++) {
				//if ((*i)->cards.empty()){cout << "empty";continue;}
				for (auto c=(*i)->cards.begin();c<(*i)->cards.end();c++) {
				cout<<(*c)->rank<<"-"<<(*c)->suit<< endl;}
			cout<<endl;} 
		
		}		
	//updates the set of possible moves, used for legality check and hints for user
	void update_possible_moves(){
		possible_moves.clear();
		if (!deck.empty()){
			Card * deckCard=deck.front();
			for (auto pile=piles.begin();pile<piles.end();++pile){
				if ((*pile)->cards.empty()){ //empty pile, king can be placed here
					if (deckCard->rank==king){
						possible_moves.push_back(new Move('d',0, pile-piles.begin(),0));
						}
					}
				else { //there are some cards on the pile
					if (deckCard->differentColorAs((*pile)->cards.front()) && deckCard->rank+1==(*pile)->cards.front()->rank) // different color and rank just below the card on the pile
					{
						possible_moves.push_back(new Move('d',0, pile-piles.begin(),0));

					}
					
					}	
					
				}
			}
		return;}
	void print_possible_moves(){
		return;}
	Game(){
		make_deck();
		srand(unsigned(std::time(0)));
		shuffle_deck();
		make_piles();
		make_foundations();
		}
	};


bool haspref(char* prefix,string str){
 if (std::equal(string(prefix).begin(), string(prefix).end(), str.begin())) {
    return true;
  } else {
    return false;
  }}
  
int main(){
	bool run=true;
	//generate deck
	Game g=Game();

	while (run){
		g.show_table();	
		g.update_possible_moves();
		string input;
		getline(cin, input);
		cout << input;
		if (input.compare("e")==0 or input.compare("exit")==0){
			run=false;
			break;
			}
		else if (input.compare("u")==0 or input.compare("undo")==0){
			if (g.undo()!=0) cout << "nejde" << endl;
			}
		else if (input.compare(0,1,"f")==0){
			short from;
			istringstream(input.substr(1,2)) >> from;
			short  to; 
			short startIdx;
			istringstream(input.substr(3,4)) >> to;
			istringstream(input.substr(5,6)) >> startIdx;
			g.make_move('f',from,to, startIdx);
			//g.make_move('f',0,0,0);
			cout << from <<" " << to << " " << " " << startIdx <<endl;
			}
		else if (input.compare(0,1,"h")==0){
			for (auto m=g.possible_moves.begin();m<g.possible_moves.end();++m) {
				cout << *m;
				}
			}
	}

	g.make_move('f',0,0,0);
	g.make_move('f',2,0,0);
	g.make_move('f',2,1,0);
	g.make_move('f',6,1,0);
	//g.make_move('f',16,1);

	g.make_move('d',0,1,0);

	g.show_table();	
	g.show_history();
	g.undo();
	g.undo();
	g.show_table();	
	g.show_history();
} 
