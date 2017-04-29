#include "game.h"
#include <QDebug>

map <Suits,  vector <string> >  faces={{spades,{"🂡 ","🂢 ","🂣 ","🂤 ","🂥 ","🂦 ","🂧 ","🂨 " ,"🂩 ","🂪 ","🂫 ","🂬 ","🂭 ","🂮 "}}, \
                                       {clubs,{"🃑","🃒","🃓","🃔","🃕","🃖","🃗","🃘","🃙","🃚","🃛","🃜","🃝","🃞"}}, \
                                       {diamonds,{"🃁","🃂","🃃","🃄","🃅","🃆","🃇","🃈","🃉","🃊","🃋","🃌","🃍","🃎"}}, \
                                       {hearts,{"🂱","🂲","🂳","🂴","🂵","🂶","🂷","🂸","🂹","🂺","🂻","🂼","🂽","🂾"}}};

Game::Game(){
    make_deck();

    //srand(unsigned(std::time(0)));
    shuffle_deck();

    make_deck_pile();

    make_piles();
    make_foundations();
}

int Game::make_deck(){
    deck=new Pile('d');
    deckBuffer=new Pile('b');
    for (short t=0;t!=4;t++){
        for (short v=0;v!=13;v++) {
            Card *c=new Card((Rank) v,(Suits) t,deck);
            deck->cards.push_back(c);
            c->pile=deck;
        }
    }
    return 0;
}
int Game::make_deck_pile(){;}

int Game::undo(){
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
        deck->cards.push_back(c);//return it to the deck
        break;
    }

    history.pop_back();
    return 0;
}
int Game::shuffle_deck() {
    random_shuffle ( deck->cards.begin(), deck->cards.end() );
    return 0;}
int Game::make_piles(){
    for (int i=0;i!=7;i++){
        Pile *p=new Pile('p');
        for (int x=0;x!=i+1;x++){
            deck->cards.back()->pile=p;
            p->cards.push_back(deck->cards.back());
            if (x==i) p->cards.back()->faceUp=true;
            deck->cards.pop_back();

        }
        piles.push_back(p);
    }
    return 0;
}

int Game::make_foundations(){
    for (int i=0;i!=4;i++){
        Pile *p=new Pile('f');
        foundations.push_back(p);
    }
    return 0;
}

int Game::move(char type,short from_pile, short to_pile, short card_idx){
    Move *m=new Move(type,from_pile, to_pile,card_idx);
    history.push_back(m);
    Card * c;
    switch (type) {
    case 'f': //pile to foundation
        c=piles.at(from_pile)->cards.back();
        foundations.at(to_pile)->cards.push_back(c);
        c->pile=foundations.at(to_pile);

        piles.at(from_pile)->cards.pop_back();
        if(!piles.at(from_pile)->cards.empty()){
            piles.at(from_pile)->cards.back()->faceUp=true;
        }
        break;
    case 'b': //from deckBuffer to pile, from_pile parameter unused
        c=deckBuffer->cards.back();
        piles.at(to_pile)->cards.push_back(c);
        c->pile= piles.at(to_pile);
        deckBuffer->cards.pop_back();
        break;
    case 'd': //from deck to deckBuffer
        c=deck->cards.back();
        deckBuffer->cards.push_back(c);
        c->faceUp=true;
        qDebug() << " rank" <<c->rank;
        deck->cards.pop_back();
        c->pile= deckBuffer;
        break;
    case 'p': //pile to pile
        c=piles.at(from_pile)->cards.at(card_idx);
        piles.at(to_pile)->cards.push_back(c);
        piles.at(from_pile)->cards.pop_back();
        if(!piles.at(from_pile)->cards.empty()){
            piles.at(from_pile)->cards.back()->faceUp=true;
        }
        c->pile=piles.at(to_pile);
        break;
    case 'g': //buffer to foundation
        c=deckBuffer->cards.back();
        foundations.at(to_pile)->cards.push_back(c);
        deckBuffer->cards.pop_back();
        c->pile=foundations.at(to_pile);
        break;
    case 'u': //buffer to foundation
        c=foundations.at(from_pile)->cards.back();
        piles.at(to_pile)->cards.push_back(c);
        foundations.at(from_pile)->cards.pop_back();
        c->pile=piles.at(to_pile);
        break;

    case 'r':
        qDebug()<<"reload";
        //std::reverse_copy (deckBuffer->cards.begin(), deckBuffer->cards.end(), deck->cards.begin());
       deck->cards=deckBuffer->cards;
        for (auto c=deck->cards.begin();c<deck->cards.end();++c){
            (*c)->pile=deck;
            (*c)->faceUp=false;
        }
        //std::reverse(deck->cards.begin(),deck->cards.end());

        deckBuffer->cards.clear();

        break;
    }
    update_possible_moves();
    return 0;
}
int Game::make_move(char type,  Pile* to_pile, Card *card)
{
    //check if legal, i.e. if the move is in the set of possible moves
    Pile * from_pile=card->pile;

    bool legal=false;

    short from_pile_idx=0;
    short to_pile_idx=0;
    short card_idx=0;
    //if card->pile->type==


    if (from_pile->type=='f')
    {
        for (auto p=foundations.begin();p<foundations.end();  ++p)
        {
            for (auto c=(*p)->cards.begin();c<(*p)->cards.end();++c){
                if (*c==card){ //su ve spravnem balicku
                    cout << "found: " <<p-foundations.begin();
                    from_pile_idx=(p-foundations.begin());
                    card_idx=c-(*p)->cards.begin();
                    break;
                }
            }
        }
    }
    else if (from_pile->type=='p'){
        for (auto p=piles.begin();p<piles.end();  ++p)
        {
            for (auto c=(*p)->cards.begin();c<(*p)->cards.end();++c){
                if (*c==card){ //su ve spravnem balicku
                    cout << "found: " <<p-piles.begin();
                    from_pile_idx=(p-piles.begin());
                    card_idx=c-(*p)->cards.begin();
                    break;
                }
            }
        }
    }
    else if (from_pile->type=='b'){
        from_pile_idx=0;
        card_idx=0;
    }
    else if (from_pile->type=='d'){
        from_pile_idx=0;
        to_pile_idx=0;

        card_idx=0;
    }
    /*for (auto p=piles.begin();p<piles.end();  ++p)
                {
                for (auto c=(*p)->cards.begin();c<(*p)->cards.end();++c){
                    if (*c==card){ //su ve spravnem balicku
                        cout << "found: " <<p-piles.begin();
                        from_pile_idx=(p-piles.begin());
                        from_pile=(*p);
                        card_idx=c-(*p)->cards.begin();
                        break;
                    }
                }
            }

            for (auto p=foundations.begin();p<foundations.end();  ++p)
                {
                for (auto c=(*p)->cards.begin();c<(*p)->cards.end();++c){
                    if (*c==card){ //su ve spravnem balicku
                        cout << "found: " <<p-foundations.begin();
                        from_pile_idx=(p-foundations.begin());
                        from_pile=(*p);
                        card_idx=c-(*p)->cards.begin();
                        break;
                    }
                }
            }
*/
    for (auto p=piles.begin();p<piles.end();  ++p)
    {
        if(*p==to_pile){
            to_pile_idx=p-piles.begin();
            break;

        }
    }
    for (auto p=foundations.begin();p<foundations.end();  ++p)
    {
        if(*p==to_pile){
            to_pile_idx=p-foundations.begin();
            break;

        }
    }
    /* if(to_pile_idx==deckBuffer){
                    to_pile_idx=p-deckBuffer.begin();
                }
        */
    cout << type << from_pile_idx << to_pile_idx << card_idx;
    // jeste projet foundations i deck

    qDebug()<<type<<from_pile_idx<<to_pile_idx<<card_idx;
    for (auto m=possible_moves.begin();m<possible_moves.end();++m){
        if ((*m)->type==type && (*m)->from_pile==from_pile_idx && (*m)->to_pile==to_pile_idx && (*m)->card_idx==card_idx)
        {legal=true;}
    }
    if (!legal) return false;
    qDebug()<<"MAKING MOVE:"<<type<<from_pile_idx<<to_pile_idx<<card_idx;
    move(type,from_pile_idx, to_pile_idx,card_idx);
    return true;
}

int Game::make_move(char type,short from_pile, short to_pile, short card_idx)
{
    //check if legal, i.e. if the move is in the set of possible moves
    bool legal=false;

    for (auto m=possible_moves.begin();m<possible_moves.end();++m){
        if ((*m)->type==type && (*m)->from_pile==from_pile && (*m)->to_pile==to_pile && (*m)->card_idx==card_idx)
        {legal=true;
        qDebug()<<"return";}
    }
    if (!legal) {
        return false;
    }
    move(type,from_pile, to_pile,card_idx);
    return true;
}
void Game::show_history(){
    for (auto it=history.begin();it<history.end();it++) {
        cout << (*it)->type << " " << (*it)->from_pile << " " << (*it)->to_pile << endl;
    }
}
void Game::show_table(){
    cout << "Deck:" << endl;
    for (auto it=deck->cards.begin();it<deck->cards.end();++it) {
        //cout << (*it);
        cout<<faces[(*it)->suit][(*it)->rank];

        //cout<<(*it)->rank<<"-"<<(*it)->suit<<",";}
        cout<<endl;}

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
void Game::update_possible_moves(){ // :(
    possible_moves.clear();
    qDebug()<<"updating";
    if (deck->cards.empty()){ //if the deck is empty, we can reload it
        possible_moves.push_back(new Move('r',0, 0,0));

    }
    else { //if there is a card in the deck, we can move it to deckBuffer
        possible_moves.push_back(new Move('d',0, 0,0));
    }

    if (!deckBuffer->cards.empty()){ // from deckBuffer to pile or foundation
        Card * deckCard=deckBuffer->cards.back();
        qDebug()<<deckCard->rank;

        for (auto pile=piles.begin();pile<piles.end();++pile){

            if ((*pile)->canPlace(deckCard)){
                possible_moves.push_back(new Move('b',0, pile-piles.begin(),0));
            }
        }
        for (auto f=foundations.begin();f<foundations.end();++f){

            if ((*f)->canPlace(deckCard)){
                possible_moves.push_back(new Move('g',0, f-foundations.begin(),0));
            }
            }

       }

        for (auto pile=piles.begin();pile<piles.end();++pile){
            for (auto c=(*pile)->cards.rbegin();(c<(*pile)->cards.rend()) && (*c)->faceUp; ++c){
                qDebug()<<"card move f "<<(*c)->rank<<(*c)->suit<<c-(*pile)->cards.rbegin();
                if ((*c)==(*pile)->cards.back()){//pokud je karta na vrcholu balicku, podivame se, jestli ji nemuzeme dat do foundations
                    for (auto f=foundations.begin(); f<foundations.end();f++){
                        if ((*f)->canPlace(*c)) {
                            possible_moves.push_back(new Move('f',pile-piles.begin(),f-foundations.begin(),(*pile)->cards.size()-1));
                        }
                    }
                }
                // pro kazdou kartu projedu vrcholky vsech balicku, jestli ji tam nemuzu dat
                for (auto topile=piles.begin();topile<piles.end();++topile){
                    if ((*topile)->canPlace(*c)){
                        possible_moves.push_back(new Move('p',pile-piles.begin(), topile-piles.begin(),std::distance(begin((*pile)->cards), c.base()) - 1));
                    }
                }

            }
        }
        //nakonec zjistime, jestli se da tahnout z foundation nekam
        for (auto f=foundations.begin(); f<foundations.end();f++){
            if (!(*f)->cards.empty()) {
                Card * c=(*f)->cards.back();
                for (auto topile=piles.begin();topile<piles.end();++topile){
                    if ((*topile)->canPlace(c)){
                        possible_moves.push_back(new Move('u',f-foundations.begin(), topile-piles.begin(),(*topile)->cards.size()-1));

                    }
                    /* if ((*topile)->cards.empty()){ //empty pile, king can be placed here
                        if (c->rank==king){
                            possible_moves.push_back(new Move('z',f-foundations.begin(), topile-piles.begin(),0));
                            qDebug()<<"added";

                            }
                        }
                    else { //there are some cards on the pile
                        if (c->differentColorAs((*topile)->cards.back()) && c->rank+1==(*topile)->cards.back()->rank) // different color and rank just below the card on the pile
                        {
                            possible_moves.push_back(new Move('z',f-foundations.begin(), topile-piles.begin(),0));
                            qDebug()<<"added";
                        }

                        }*/
                }
            }
        }


        return;}
    void Game::print_possible_moves(){
        for (auto m=possible_moves.begin();m<possible_moves.end();++m){
            qDebug() << (*m)->type << (*m)->from_pile << (*m)->to_pile << (*m)->card_idx;
        }
        return;}





