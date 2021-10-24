#include "blackjack.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;
/*________________

	CARD METHODS
__________________*/

//the Card constructor takes a rank and suit and returns a card
//this constructor is only used in the populate() method of the Deck Class
Card::Card(Type suit, Rank rank)
{
	pSuit = suit;
	pRank = rank;
}

//the getValue method uses a switch statement to check what rank the card is and returns the correct integer 
int Card::getValue(){
	switch(pRank){
		case ACE:
			return 11;
			break;
		case TWO:
			return 2;
			break;
		case THREE:
			return 3;
			break;
		case FOUR:
			return 4;
			break;
		case FIVE:
			return 5;
			break;
		case SIX:
			return 6;
			break;
		case SEVEN:
			return 7;
			break;
		case EIGHT:
			return 8;
			break;
		case NINE:
			return 9;
			break;
		case TEN:
			return 10;
			break;
		case JACK:
			return 10;
			break;
		case QUEEN:
			return 10;
			break;
		case KING:
			return 10;
			break;
		}
}
//the displayCard method first checks if the card is a Ten, Jack, Queen, King, or Ace by assigning the int variable 'x' to getValue and then comparing 'x' to 10
//If the value of the card is greater than or equal to 10, the char variable 'r' is assigned a letter (T, J, Q, K, A) denoting its value
//If the value of the card is less than 10, 'r' is assigned the value ('0' + x), which will return the card's value as a character
//The char variable 's' is assigned using a switch statement and will represent the card's suit
//the variables 'r' and 's' are then printed to screen, unless the card's rank is TEN
//Since the number '10' cannot be stored in a char value, this special case is dealt with by just printing '10'
void Card::displayCard(){
	char r;
	int x = getValue();
	if (x >= 10)
	{
		if (pRank == TEN){
			r = 'T';
		}
		else if (pRank == JACK){
			r = 'J';
		}
		else if (pRank == QUEEN){
			r = 'Q';
		}
		else if (pRank == KING){
			r = 'K';
		}
		else if (pRank == ACE){
			r = 'A';
		}
	}
	else{	r = '0' + x;
		}
	char s;
	switch(pSuit){
		case HEARTS:
			s = 'H';
			break;			
		case SPADES:
			s = 'S';
			break;			
		case CLUBS:
			s = 'C';
			break;			
		case DIAMONDS:
			s = 'D';
			break;			
	}
	if(r == 'T'){
		cout << 10;
	}

	else{cout << r ;}

	cout << s ;
}

/*________________

	HAND METHODS
__________________*/


//the add method adds the input card to the hand
//Hands are implemented using a vector, so the vector method push_back() is used to add the card to the hand
//this method is used by the deal() method of the Deck Class  
void Hand::add(Card& card){
	hand.push_back(card);
}

//the displayHand method is a helper method that I added to help with printing the hands during the game
//it uses a simple vector for loop to iteratively call the displayCard() method and add a space after each card
void Hand::displayHand(){
	for (std::vector<Card>::iterator i = hand.begin(); i != hand.end(); ++i)
	{
		i -> displayCard();
		cout<<" ";
	}
}

//the clear method empties the Hand it is called for
//If the hand field of the class Hand was not private, this method would not be required, as it just calls the vector method clear() on the hand field 
void Hand::clear(){
	hand.clear();
}

//the getTotal method finds the sum of the cards in a hand
//the integer 'x' is initialized as 0, and the values from the getValue call are iteratively added
//After the first loop, the method checks if the total is greater than 21
//If the total is >21, the method loops through the cards to check if there is an Ace in the hand, and subtracts 10 per Ace until x is below 21 or there are no more cards to check

int Hand::getTotal(){
	int x = 0;
	if (hand.size() == 0){ return 0;}
	for (std::vector<Card>::iterator i = hand.begin(); i != hand.end(); ++i)
	{
		int y = i -> getValue();
		x += y;
		
	}
	if(x>21){
		for (std::vector<Card>::iterator i = hand.begin(); i != hand.end(); ++i)
		{
			if(i -> getValue() == 11){
				x= x - 10;
				if(x <= 21){return x;}
			}
		}

	}
	return x;
}

/*________________

	DECK METHODS
__________________*/

//the populate method uses a for loop to iterate through the suits, and a nested for loop to iterate through the ranks
//it also uses the static_cast() method on both the Type and Rank enums to create each card
//the result is a deck that contains all 52 standard cards
void Deck::populate(){

	for (int i = 0; i<4; ++i){
		
		Card::Type s = static_cast<Card::Type>(i);
		for (int j = 1; j < 14; ++j)
		{
			Card::Rank r = static_cast<Card::Rank>(j);
			Card c = Card(s, r);
			deck.push_back(c);
		}
	}
	deck.shrink_to_fit();
}

//this is a helper random function that will be used in the shuffle() method
int myrandomfunc(int j){
	int x = rand()*unsigned(time(NULL));

	return x%j;
}

//the shuffle method randomizes the order of the cards in the deck vector
//the above function myrandomfunc() is used in the call of random_shuffle to generate a unique random shuffle each call, rather than the same random shuffle
void Deck::shuffle(){
	random_shuffle(deck.begin(),deck.end(), myrandomfunc);
}

//the deal method will add a card to the input hand
//the card is then removed from the deck using the vector method pop_back()
void Deck::deal(Hand& h){
	Card c = deck.back();
	h.add(c);
	deck.pop_back();

}

/*________________

	PLAYER METHODS
__________________*/

//the AbstractPlayer constructor
AbstractPlayer::AbstractPlayer(){};

//the isBusted method checks if the player's total has exceeded 21
//If it has, the method returns true. else, false 
bool AbstractPlayer::isBusted(){
	if(getTotal()>21){
		return true;
	}
	else{
		return false;
	}
}

//the isDrawing method asks the HumanPlayer if they would like to keep drawing cards
//it asks this by printing the players options: draw (d) or stay (s), and storing the response in the character variable 'a'
//if 'a' is not 'd' or 's', the method asks for a proper input and asks again until proper input is given
bool HumanPlayer::isDrawing(){
	bool nodecision = true;
	bool draw;
	while(nodecision){
		cout<< "What would you like to do?"<<endl;
		cout<< "draw or stay? (d/s)";
		char a;
		cin >> a;
		if(a== 'd'){
			nodecision = false;
			draw = true;
		}
		else if(a == 's'){
			nodecision = false;
			draw = false;
		}
		else{
			nodecision = true;
			cout<< "Please enter a valid response."<<endl;

		}
	}
	return draw;
}

//the announce method takes a character representing the outcome of the game as input
//'l'=loss, 'w'=win, 'p'= push
//the metthod will output the proper response given the parameters
void HumanPlayer::announce(char r){
	if (r == 'l'){
		cout<< "Casino wins" << endl;
		return;
	}
	else if(r == 'w'){
		cout<< "Player wins"<<endl;
		return;
	}
	else if(r == 'p'){
		cout<< "Push: No one wins."<<endl;
	}
}

//the isDrawing method for the ComputerPlayer checks if the total of the ComputerPlayer's hand exceeds oor is equal to 16
//if this is the case, the method returns false, denoting that the ComputerPlayer will stay
//Otherwise, returns true  
bool ComputerPlayer::isDrawing(){
	if(getTotal()<=16){
		return true;
	}
	else{return false;}
}

/*________________

	GAME METHODS
__________________*/

BlackJackGame::BlackJackGame(){};


//The play method defines the framework for how all the other methods and classes interact while the game is being played
//the method begins by populating the deck, shuffling, and dealing 3 cards, one to the Casino and two to the Player
//The two hands are printed to the screen along with the value of each so far
//the Player then decides if they would like to draw again
//If yes, the following occurs: a card is added to the player's hand, the hand is printed, the method checks if the player is busted, and if not asks if they want to draw another card
//If the player busts, the loop is exited and the announce() method is called with character 'l' to denote the player losing
//If the player stays, the loop is exited and the Casino takes their turn
//If the Casino busts, the loop is exited and the announce() method is called with character 'w' to denote the player winning
//After the Casino finishes drawing, the total of the 2 Hands are compared, and the announce() method wil be called with the proper input from the result of the comparison
//After the announce() method is called, both hands are cleared, and the method ends
//The hands are cleared in case the player would like to play another round, in which case the hands would need to start empty
void BlackJackGame::play(){
	m_deck.populate();
	m_deck.shuffle();
	m_deck.deal(m_casino);
	cout<< "Casino: ";
	m_casino.displayHand();
	int c_tot = m_casino.getTotal();
	cout << "[" + to_string(c_tot) + "]"<<endl;
	HumanPlayer p;
	m_deck.deal(p);
	m_deck.deal(p);

	bool draw = true;

	while(draw){

		cout<<"Player: ";
		p.displayHand();
		int p_tot = p.getTotal();
		cout << "[" + to_string(p_tot) + "]"<<endl;
		if(p.isBusted()){
			draw = false;
		}
		else if(p.isDrawing()){
			m_deck.deal(p);
			draw = true;
		}
		else{draw = false;}
	}
	if(p.isBusted()){
		cout<< "Player busts"<<endl;
		p.announce('l');
	}

	else{
		while(m_casino.isDrawing()){
			m_deck.deal(m_casino);
			cout<< "Casino: ";
			m_casino.displayHand();
			c_tot = m_casino.getTotal();
			cout << "[" + to_string(c_tot) + "]"<<endl;
			if(m_casino.isBusted()){
				break;
			}

		}
		if(m_casino.isBusted()){
			cout<<"Casino busts"<<endl;
			p.announce('w');
		}
		else if(m_casino.getTotal()>p.getTotal()){
			p.announce('l');
		}
		else if(m_casino.getTotal()<p.getTotal()){
			p.announce('w');
		}
		else{p.announce('p');}
	}
	m_casino.clear();
	p.clear();
	m_deck.deck.clear();
}





