//---------------------------------------------------------------------------
//Program name: cards.cpp
//Author: Bobby Bose
//Purpose: Main program for the cards game/program. Uses linkedLists to simulate game
//---------------------------------------------------------------------------

//Compiler Directives
#include <string>									//To record which card was given for printing purposes
#include <iostream>									//For cin/cout statements
#include "linkedList.h"								//linkedList class simulates the player's decks

using namespace std;

//Function prototypes
void readingNumbers(int &advantagePlayer, int &cardGiven, int &recievingPlayer, int numberOfPlayers);
void cardExchange(int cardGiven, int advantagePlayer, int recievingPlayer, string &whichCardTaken, linkedList listOfPlayers[]);

//Make function for the program
int main(int argc, char* argv[]) {

	//Making sure the number of command line arguments was included
	if (argc != 4) {
		cout << "Usage: ./cards numPlayers numCards numTurns" << endl;
		return 1;
	}

 
	//How many players are in the game
	int numPlayers = atoi(argv[1]);
	//How many cards the players start with
	int numStartingCards = atoi(argv[2]);
	//What the maximum number of turns allowed is
	int maxTurns = atoi(argv[3]);


	//Checking that the arguments makes sense
	if (numPlayers < 1 || numStartingCards < 1 || maxTurns < 0) {
		cout << "The number of players and cards must be positive;" << endl;
		cout << "the number of turns must be >= 0" << endl;
		return 2;
	}

    
	//What the current turn is
	int currTurn = 1;

	//Linked list of the player's pile's of cards
	linkedList players[numPlayers];

	//Populating the player's piles with cards
	for (int i = 0; i < numPlayers; i += 1) {
		for (int j = 0; j < numStartingCards; j += 1) {
			players[i].insertAtEnd(j + 1);
		}
	}


	//Until the game hits the maximum allowed of turns
	while (currTurn <= maxTurns) {

		//Which player is giving up a card
		int playerAdvantageDice;
		//Which card the player is giving up
		int discardDice;
		//Which player is accepting a card
		int playerAcceptDice;
		//To record where the player needs to discard a card from. For the cout statement later
		string topOrBottom;

		//Reading the random numbers from the script and calculating the dice rolls
		readingNumbers(playerAdvantageDice, discardDice, playerAcceptDice, numPlayers);

		//Exchanging the cards between the two players
		cardExchange(discardDice, playerAdvantageDice, playerAcceptDice, topOrBottom, players);


		//Printing out what happened this turn
		cout << "turn " << currTurn << ": player " << playerAdvantageDice << " sends a card to " << playerAcceptDice << ", from " << topOrBottom << endl;

		//Printing out the current weights of each player's deck
		for(int i = 0; i < numPlayers; i += 1){
			cout << "       player " << i+1 << ": weight: " << players[i].getWeight() << endl;
		}


		//Checking if a player has no more cards, and ending the game if they do
		for(int i = 0; i < numPlayers; i += 1){
			if(players[i].getWeight()==0){
				cout << "Game is over; player " << i+1 << " has no cards left." << endl;
				return 0;
			}	
		}


		//Incrementing the current turn by one
		currTurn += 1;
	}

	
	//Player with the lowest weight of cards left. Assuming it is player 1
	int lowestWeightPlayer = 0;

	//Cycling through all the players
	for(int i = 1; i < numPlayers; i += 1){

		//If the current player has a smaller weight the previously lowest weight player
		if( players[i].getWeight() < players[lowestWeightPlayer].getWeight() )
			//Make them the new lowest weight player
			lowestWeightPlayer = i;
	}

	//Printing out which player has the lowest weight.
	cout << "No more turns.  Player " << lowestWeightPlayer+1 << " wins." << endl;

	return 0;
}



//Given: the advantage player, which card to give, the recieving players, and the number of total players
//Returns: None
//Reads random numbers from the perl script and calculates the dice rolls for a turn
void readingNumbers(int &advantagePlayer, int &cardGiven, int &recievingPlayer, int numberOfPlayers){
	
	//Hold the value of the random number read
	int readNum;

	//Reading a random number
	cin >> readNum;
	//Calculating which player has the advantage this turn
	advantagePlayer = (readNum % numberOfPlayers) + 1;
	
	//Reading a random number
	cin >> readNum;
	//Calculating which card the player needs to give up
	cardGiven = (readNum % 2) + 1;

	//Reading a random number
	cin >> readNum;
	//Calculating which player is going to recieve the random card
	recievingPlayer = (readNum % numberOfPlayers) + 1;

}



//Given: which card to give, the advantage player, the recieving player, a string to hold which card was given, and the linkedList of players
//Returns: None
//Performs the card exchange between the advantage and recieving players
void cardExchange(int cardGiven, int advantagePlayer, int recievingPlayer, string &whichCardTaken, linkedList listOfPlayers[]){
	
	//What the value of the card taken was
	int valueTaken;

	//If the player rolled a 1
	if(cardGiven==1){
		//Player must discard the top card
		valueTaken = listOfPlayers[advantagePlayer-1].removeAtFront();
		whichCardTaken = "top";
	}
	//Otherwise, the player rolled a 2
	else{
		//Player must discard the bottom card
		valueTaken = listOfPlayers[advantagePlayer-1].removeAtEnd();
		whichCardTaken = "bottom";
	}

	//Adding the new card to the top of the recipient's deck
	listOfPlayers[recievingPlayer-1].insertAtFront(valueTaken);
}
