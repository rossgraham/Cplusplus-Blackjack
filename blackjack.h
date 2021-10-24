#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

//This file contains all the declarations oof the classes that will be used in the blackjack game
//I will go into further detail about individual methods in the blackjack.cpp file

class Card{
	public:
		enum Type {SPADES, CLUBS,  HEARTS, DIAMONDS};
		enum Rank {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
		Card(Type suit, Rank rank);
		int getValue();
		void displayCard();
	private:
		Type pSuit;
		Rank pRank;

};

class Hand{
	public:
		void add(Card& card);
		void clear();
		int getTotal();
		void displayHand();
	
	private:
		std::vector<Card> hand;
};

class Deck{
	public:
		void populate();
		void shuffle();
		void deal(Hand& h);
		std::vector<Card> deck;
};

class AbstractPlayer: public Hand{
	public:
		virtual bool isDrawing() = 0;
		bool isBusted();
		AbstractPlayer();
	

};
class HumanPlayer: public AbstractPlayer{

	public:
		void announce(char r);
		bool isDrawing();

	

};

class ComputerPlayer: public AbstractPlayer
{
	public:
		bool isDrawing();
	

};

class BlackJackGame
{
	public:
		void play();
		BlackJackGame();
	private:
		Deck m_deck;
		ComputerPlayer m_casino;

};
