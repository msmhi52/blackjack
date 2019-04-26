#ifndef _BLACK_JACK_
#define _BLACK_JACK_
#include <string>

using std::string;

        //////*************** CARD ***************//////
class card_t{
public:
        string card_num;
	string shape; //node data
	
	card_t(string card_num, string shape);
	~card_t();
	
	card_t *next; //pointer to next card node
	card_t *prev; //pointer to previous card node
	
 
};
        

        /////************* BLACKJACK **************////
class black_jack_t{
public:
	black_jack_t(); //class constructor
	black_jack_t(int initmny, int money);
	~black_jack_t();
	
	int initmny;
	int money;	
		
	// FUNCTIONS
	int bet();
	void shuffle();
	void distribute(black_jack_t &object);
	int pturn(black_jack_t &object, black_jack_t &dealer, black_jack_t &black_jack, int bet_money);
	int dturn(black_jack_t &object, black_jack_t &player, black_jack_t &black_jack, int bet_money);
	int winorlose(black_jack_t &player, black_jack_t &dealer, int bet_money);
	
	//OTHER FUNCTIONS
	string* num2alp(int card[]);
	string* num2shape(int card[]);
	int sumofcard();
	void dsply_dcard();
	void dsply_pcard(int sum);
	void clear_screen();
        
        //deck data
        card_t *head;
        card_t *tail;
        int count;

};




#endif 
