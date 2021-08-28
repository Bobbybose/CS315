//---------------------------------------------------------------------------
//Program name: linkedList.cpp
//Author: Bobby Bose
//Purpose: Implementation of the linkedList class.
//---------------------------------------------------------------------------

//Compiler Directives
#include "linkedList.h"

using namespace std;

//Given: None
//Returns: None
//Constructor for the linked list
linkedList::linkedList() {
	
	//Setting size of the new list to 0
	size = 0;

	//Setting the head to 0 (essentially NULL)
	head = 0;

	//Setting the rear to 0 (essentially NULL)
	rear = 0;
}

//Given: None
//Returns: size of list
//Accessor for the size of the list
int linkedList::getSize() {
	
	//Returning the size of the list
	return size;
}

//Given: Card value to add
//Returns: None
//Adds a new node (card) to the front of the list
void linkedList::insertAtFront(int value) {
	
	//Making a new node for the new card and giving it the given value
	node* newCard = new node;
	newCard->cardValue = value;

	//If the list is currently empty
	if (size == 0) {
		//Set the new card's previous and next to nothing
		newCard->next = 0;
		newCard->prev = 0;

		//New card is now the head and rear of the list
		head = newCard;
		rear = newCard;

		//Size of list increases by 1
		size += 1;
	}

	//Otherwise if list has at least one card already
	else {
		//The new card's next is the previous head, and it has no previous
		newCard->next = head;
		newCard->prev = 0;

		//The old head is after the new card
		head->prev = newCard;

		//Making the new card the new head
		head = newCard;

		//Size of list increases by 1
		size += 1;
	}
}

//Given: None
//Returns: Value of card at front or -1 if there are no more cards
//Removes a node (card) from the front of the list
int linkedList::removeAtFront() {
	
	//Variable for the value of the card being removed
	int answer;
	
	//If the list is empty, just return -1
	if (size == 0)
		return -1;

	//Otherwise, if the list is not empty
	else {
		//Recording the card being removed's value
		answer = head->cardValue;

		//The new head is the card after the current head
		head = head->next;

		//Decrease the size of the list by 1
		size -= 1;

		//Return the removed card's value
		return answer;
	}
}

//Given: Card value to add
//Returns: None
//Adds a new node (card) to the end of the list
void linkedList::insertAtEnd(int value) {
	
	//Making a new node for the new card and giving it the given value
	node* newCard = new node;
	newCard->cardValue = value;

	//If the list is currently empty
	if (size == 0) {
		//Set the new card's previous and next to nothing
		newCard->next = 0;
		newCard->prev = 0;

		//New card is now the head and rear of the list
		head = newCard;
		rear = newCard;

		//Size of list increases by 1
		size += 1;
	}

	//Otherwise if list has at least one card already
	else {
		//The new card's previous is the previous rear, and it has no next
		newCard->next = 0;
		newCard->prev = rear;

		//the old rear is before the new card
		rear->next = newCard;

		//Making the new card the new rear
		rear = newCard;

		//Size of list increases by 1
		size += 1;
	}
}

//Given: None
//Returns: Value of card at end or -1 if there are no more cards
//Removes a node (card) from the end of the list
int linkedList::removeAtEnd() {

	//Variable for the value of the card being removed
	int answer;

	//If the list is empty, just return -1
	if (size == 0)
		return -1;

	//Otherwise, if the list is not empty
	else {
		//Recording the card being removed's value
		answer = rear->cardValue;

		//The new rear is the card before the current rear
		rear = rear->prev;

		//Decrease the size of the list by 1
		size -= 1;

		//Return the removed card's value
		return answer;
	}
}

//Given: None
//Returns: Weight of list
//Calculates and returns the weight of the stack of cards
int linkedList::getWeight() {
	
	//If the list is empty
	if (size == 0)
		//Return a weight of 0
		return 0;

	//Variable to hold the weight
	int weight = 0;
	//Variable to hold what the current depth is
	int depth = 1;

	//Start at the head of the list
	node* currCard = head;
	
	//Until we reach the rear
	while (currCard != rear) {
		//Add the current card's weight to the total weight
		weight += currCard->cardValue * depth;

		//Increase the depth by 1
		depth += 1;

		//Move on to the next card in the list
		currCard = currCard->next;
	}

	//Add the weight of the rear too
	weight += rear->cardValue * depth;

	//Returning the weight
	return weight;

}

