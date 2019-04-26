#include <iostream>
#include <cstdlib>
#include "blackjack.h"

using namespace std;

int main(int argc, char* argv[]){

	black_jack_t black_jack(0, 0);
        black_jack_t deck; //class constructor
        black_jack_t dealer;
        black_jack_t player;
        
	int bet_money;
	int game_set;
	
	if(argc!=1){
		black_jack.initmny = atoi(argv[1]);
	}
	else{
		black_jack.initmny = 5000;
	}
	
	black_jack.money = black_jack.initmny;

        //GAME START    	
        while(1){
	bet_money = black_jack.bet();
	if(bet_money == -1) {return 0;}
	
	deck.shuffle();
	
        cout << "[Salary: " << black_jack.money << "]  [Amount of Bet: " << bet_money <<"]" << "\n" <<
        "------------------------------------------ \n";
        
	player.distribute(deck);
	dealer.distribute(deck);
	player.distribute(deck);
	dealer.distribute(deck);
        
        int psum = player.sumofcard();
        
        dealer.dsply_dcard();
        player.dsply_pcard(psum);        
        
        if(psum == 21){
                black_jack.money += bet_money * 3;
                cout << "*B*L*A*C*K*J*A*C*K*" << "\n" << "You earned " << bet_money * 3 << 
                " which is triple of your bet!!" << "\n\n";
        }
        else{
                cout << "Hit or Stay? ";
                game_set = player.pturn(deck, dealer, black_jack, bet_money);
                if(game_set == -1) {goto endgame;}
                cout << "\nPlayer turn ends...\n\n";
                
                cout << "[Salary: " << black_jack.money << "]  [Amount of Bet: " << bet_money <<"]" << "\n" <<
                         "------------------------------------------ \n";
                cout <<"<Dealer> ";
                card_t *current_node = dealer.head;
                while(current_node){
                        cout << " [" << current_node->shape <<" "<< current_node->card_num <<"] ";
                        current_node = current_node -> next;
                }
                cout << ", Sum = " << dealer.sumofcard() << "\n";
                player.dsply_pcard(player.sumofcard());
                dealer.dturn(deck, player, black_jack, bet_money);
                 
                black_jack.winorlose(player, dealer, bet_money);
        }
        endgame:
        player.~black_jack_t();
        dealer.~black_jack_t();
        }
        
	return 0;
}
