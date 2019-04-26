#include <iostream>
#include <string>
#include <cstdlib>
#include "blackjack.h"

using namespace std;

int black_jack_t::bet() {
	int bet_money;
	
	while(1){
			if(initmny*100 < money){ //Case A
			cout << "You earned enormous money and you got busted by casino!!!" << "\n" << 
			"You earned " << money << "in casino starting with " << initmny << "!!!" << endl;
			break;
		}
		else if(money == 0){ // Case B
			cout << "You've wasted all of your money...." << endl;
			break;
		}
		
		cout << "[Current salary = $" << money << "] Select your betting money! <0 for Exit> ";
		cin >> bet_money;
		
		if(bet_money  == 0){
			cout << "You brought $" << initmny << " and left $" << money << "." << endl;
			break;
		}
		else if(bet_money > money || bet_money < 0){
			cout << "Please put valid number!!" << "\n";
		}
		else{
		        money -= bet_money;
		        return bet_money;
		}
	}
	
	
	return -1;
}

void black_jack_t::shuffle(){
        if(!tail){ //start first turn
                cout << "\n" << "Shuffling cards...\n\n";
                int card[52] = {0,1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 
                       23, 24, 25, 26, 27, 28, 29,  30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 
                       44, 45, 46, 47, 48, 49, 50,  51};
	        srand(time(NULL));
                 for (size_t i=0; i<52 ;i++) { 
                        int r = i + (rand() % (52 -i)); 
                        swap(card[i], card[r]); 
                  } 
                 string *shapeofcard = num2shape(card);
                 string *numofcard = num2alp(card);
                 
                  //making deck doubly linked list
                  head = tail = new card_t(numofcard[0], shapeofcard[0]);
                  count++;
                  for(size_t i =1; i<52; i++){
                        card_t *new_node = new card_t(numofcard[i], shapeofcard[i]);
                        tail->next = new_node;
                        new_node->prev = tail;
                        tail = new_node;
                        count++;
                  }
                  delete[] shapeofcard;
                  delete[] numofcard;
        }
        else{ // after betting
                if(count<26){ //when cards are less than 26 in deck.
                cout << "\n" << "Shuffling cards...\n\n";
                    card_t *current_node = head; // delete all lists
                    while(current_node) {
                        card_t *old_node = current_node;
                        current_node = current_node->next;
                        delete old_node;
                    }
                    head = tail = NULL;
                    count = 0;
                 int card[52] = {0,1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 
                               23, 24, 25, 26, 27, 28, 29,  30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 
                               44, 45, 46, 47, 48, 49, 50,  51};
	                srand(time(NULL));
                         for (size_t i=0; i<52 ;i++) { 
                                int r = i + (rand() % (52 -i)); 
                                swap(card[i], card[r]); 
                          } 
                         string *shapeofcard = num2shape(card);
                         string *numofcard = num2alp(card);
                         
                          //making deck doubly linked list
                          head = tail = new card_t(numofcard[0], shapeofcard[0]);
                          count++;
                          for(size_t i =1; i<52; i++){
                                card_t *new_node = new card_t(numofcard[i], shapeofcard[i]);
                                tail->next = new_node;
                                new_node->prev = tail;
                                tail = new_node;
                                count++;
                          }
                          delete[] shapeofcard;
                          delete[] numofcard;
                } 
        }//26 이상일 때 deck은 변화가 없다.
}       

	
void black_jack_t::distribute(black_jack_t &object){
        if(!tail){
                card_t *old_node = object.tail;
                object.tail = old_node->prev;
                object.tail->next = NULL;
                head = tail = old_node;  
                object.count--;
                count++;
                }
        else{
               card_t *old_node = object.tail;
               object.tail = old_node->prev;
               object.tail->next = NULL;
               tail->next = old_node;
               old_node->prev = tail;
               tail = old_node;
               object.count--;
               count++;
        }
}
	
int black_jack_t::pturn(black_jack_t &object, black_jack_t &dealer,  black_jack_t &black_jack, int bet_money){
        int psum;
        string S;
        while(S != "Stay"){
                cin >> S;
                if(S == "hit" || S == "HIT" || S == "Hit"){
                       card_t *old_node = object.tail;
                       object.tail = old_node->prev;
                       object.tail->next = NULL;
                       tail->next = old_node;
                       old_node->prev = tail;
                       tail = old_node;
                       object.count--;
                       count++;
                       
                       clear_screen();
                       psum = sumofcard();
                       cout << "[Salary: " << black_jack.money << "]  [Amount of Bet: " << bet_money <<"]" << "\n" <<
                         "------------------------------------------ \n";
                       dealer.dsply_dcard();
                       dsply_pcard(psum); 
                       
                       if(psum < 21) {
                               cout << "Hit or Stay? ";
                               return pturn(object, dealer, black_jack, bet_money);
                       }
                       else if(psum == 21){
                                black_jack.money += bet_money * 3;
                                cout << "*B*L*A*C*K*J*A*C*K*" << "\n" << "You earned " << bet_money * 3 << 
                                " which is triple of your bet!!" << "\n";
                                return -1;
                        }
                       else     return 0;
                }
                else if(S == "Stay"){}
                else{
                        cout << "\n\nPlease insert vaild expression!" << "\n";
                        return pturn(object,dealer, black_jack, bet_money);
                }
        }
        return 0;
}	

int black_jack_t::dturn(black_jack_t &object, black_jack_t &player, black_jack_t &black_jack, int bet_money){
        int dsum = sumofcard();
        char ch;
        
        if(dsum < 16){
                cout << "Dealer hits...";
                card_t *old_node = object.tail;
                object.tail = old_node->prev;
                object.tail->next = NULL;
                tail->next = old_node;
                old_node->prev = tail;
                tail = old_node;
                object.count--;
                count++;
                   
                cin.get(ch);

                if(ch == '\n') clear_screen();
                dsum = sumofcard();
                cout << "[Salary: " << black_jack.money << "]  [Amount of Bet: " << bet_money <<"]" << "\n" <<
                         "------------------------------------------ \n";
                cout <<"<Dealer> ";
                card_t *current_node = head;
                while(current_node){
                         cout << " [" << current_node->shape <<" "<< current_node->card_num <<"] ";
                         current_node = current_node -> next;
                }
                cout << ", Sum = " << dsum << "\n";
                player.dsply_pcard(player.sumofcard());
                
                return dturn(object, player, black_jack, bet_money);
        }
        else{
           cout << "Dealer stays..." << endl; 
           return 0;
        }
}

int black_jack_t::winorlose(black_jack_t &player, black_jack_t &dealer, int bet_money){
        if(player.sumofcard() > 21) {
                cout << "Busted!! You lose. You lost all of your money.\n"; 
                return 0;
        }
        
        if(dealer.sumofcard() == 21) {
                cout << "Dealer is *B*L*A*C*K*J*A*C*K*\n" <<  "You lost all of your money.\n";
        }
        else if(dealer.sumofcard() > 21){
                money += bet_money*2;
                cout << "Player won!! You earned " << bet_money * 2 << "\n";
        }
        else{
                if(player.sumofcard() >=  dealer.sumofcard()){
                        money += bet_money*2;
                        cout << "Player won!! You earned " << bet_money * 2 << "\n";
                }
                else{
                        cout << "Player lost.\n" <<  "You lost all of your money.\n";
                }
        }
        return 0;
}
	
	///////////////////////////////////////////////
	//////////construtors and destructors//////////     
card_t::card_t( string card_num, string shape):
	next(NULL),
	prev(NULL),
	card_num(move(card_num)),
	shape(move(shape)){
	}
	
	//node destructor
card_t::~card_t(){}
        
black_jack_t::black_jack_t(int initmny, int money):
        initmny(initmny),
        money(money),
        tail(NULL),
        head(NULL){
        }
        
black_jack_t::black_jack_t():
        tail(NULL),
        head(NULL),
        count(0){
        }

black_jack_t::~black_jack_t(){
        card_t *current_node = head;
        while(current_node) {
        card_t *old_node = current_node;
        current_node = current_node->next;
        delete old_node;
        }
         head = tail = NULL;
         count = 0;
}


