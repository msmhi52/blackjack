#include <string>
#include <iostream>
#include <cstdlib>
#include "blackjack.h"


using namespace std;

string* black_jack_t::num2alp(int card[]){
        string* numofcard = new string[52];
                 for (size_t i=0; i<52;i++){
                        switch(card[i]%13){
                        case 0:
                        numofcard[i] = "A";
                        break;
                        case 1:
                        numofcard[i] = "2";
                        break; 
                        case 2:
                        numofcard[i] = "3";
                        break;
                        case 3:
                        numofcard[i] = "4";
                        break;
                        case 4:
                        numofcard[i] = "5";
                        break;
                        case 5:
                        numofcard[i] = "6";
                        break;
                        case 6:
                        numofcard[i] = "7";
                        break;
                        case 7:
                        numofcard[i] = "8";
                        break;
                        case 8:
                        numofcard[i] = "9";
                        break;
                        case 9:
                        numofcard[i] = "10";
                        break;
                        case 10:
                        numofcard[i] = "J";
                        break;
                        case 11:
                        numofcard[i] = "Q";
                        break;
                        case 12:
                        numofcard[i] = "K";
                        break;
                        }
                }
                return numofcard;
}

string* black_jack_t::num2shape(int card[]){
        string* shapeofcard = new string[52];
                 for (size_t i=0; i<52;i++){
                        switch(card[i]/13){
                        case 0:
                        shapeofcard[i] = "S";
                        break;
                        case 1:
                        shapeofcard[i] = "C";
                        break; 
                        case 2:
                        shapeofcard[i] = "D";
                        break;
                        case 3:
                        shapeofcard[i] = "H";
                        break;
                        
                 }
                 }
                 return shapeofcard;
}

int black_jack_t::sumofcard(){
        size_t sum = 0, a_count = 0;
        //summing whole card number anything but A
        card_t *current_node = head;
        while(current_node){
                if (current_node->card_num == "J" || current_node->card_num == "Q" || current_node->card_num == "K"
                || current_node->card_num == "10"){
                        sum += 10;
                }
                else if(current_node->card_num == "A") {a_count++;}
                else{
                        sum += atoi(current_node->card_num.c_str());
                }
                current_node = current_node -> next;
        }
        //summing A
        while(a_count){
                if(sum + 11 > 21){
                        sum += 1;
                        a_count--;
                }
                else{
                        sum += 11;
                        a_count--;
                }
        }
        
        return sum;

}


void black_jack_t::dsply_dcard(){
        cout <<"<Dealer> [????] ";
        card_t *current_node = head->next;
        while(current_node){
                cout << " [" << current_node->shape <<" "<< current_node->card_num <<"] ";
                current_node = current_node -> next;
        }
        if(tail->card_num == "A") {cout << ", Sum = 11" << "\n";}
        else if(tail->card_num == "J" || tail->card_num == "Q" || tail->card_num == "K"){
                cout << ", Sum = 10" << "\n";
        }
        else{
                cout << ", Sum = " << tail->card_num << "\n";
        }
}

void black_jack_t::dsply_pcard(int sum){
        cout <<"<Player>";
        card_t *current_node = head;
        while(current_node){
                cout << " [" << current_node->shape <<" "<< current_node->card_num <<"] ";
                current_node = current_node -> next;
        }
        cout << ", Sum = " << sum << "\n";

}

void black_jack_t::clear_screen()
{
#ifdef WINDOWS
    std::system("cls");
#else
    // Assume POSIX
    std::system ("clear");
#endif
}
