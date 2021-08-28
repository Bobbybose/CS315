//---------------------------------------------------------------------------
//Program name: linkedList.h
//Author: Bobby Bose
//Purpose: Interface of the linkedList class.
//---------------------------------------------------------------------------

using namespace std;

//Struct for the node
//Each node has a pointed to the next and previous nodes, and a card value
struct node {
    int cardValue;
    node* next;
    node* prev;
};

class linkedList {
public:
	//Given: None
	//Returns: None
	//Constructor for the linked list
	linkedList();

	//Given: None
	//Returns: size of list
	//Accessor for the size of the list
	int getSize();

	//Given: Card value to add
	//Returns: None
	//Adds a new node (card) to the front of the list
	void insertAtFront(int value);

	//Given: None
	//Returns: Value of card at front
	//Removes a node (card) from the front of the list
	int removeAtFront();

	//Given: Card value to add
	//Returns: None
	//Adds a new node (card) to the end of the list
	void insertAtEnd(int value);

	//Given: None
	//Returns: Value of card at end
	//Removes a node (card) from the end of the list
	int removeAtEnd();

	//Given: None
	//Returns: Weight of list
	//Calculates and returns the weight of the stack of cards
	int getWeight();

private:
	int size;					//Keeps track of how many nodes (cards) are in the list
	node* head;					//Points to the front of the list
	node* rear;					//Points to the end of the list

};
