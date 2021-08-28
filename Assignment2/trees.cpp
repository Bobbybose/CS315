//---------------------------------------------------------------------------
//Program name: trees.cpp
//Author: Bobby Bose
//Purpose: Program creates a tree using user input, and performs basic tree functions to showcase how trees work.
//---------------------------------------------------------------------------


//Compiler Directives
#include <iostream>


using namespace std;


//Struct for the nodes that make up the trees
struct node {
	int values [3];		//Each node has integer values, an X, Y, and Z.
	node* left;			//Each node points to another node on its left.
	node* right;		//Each node points to another node on its right.
};


//Function prototypes
void insertInTree(node* head, int newValues[], int basedOnWhich);
node* searchTree(node* head, int whichValue, int searchValue);
void symmetricPrint(node* head);
void preOrderTraversal(node* head1, node* head2, bool firstRun);
void postOrderPrint(node* head);


//Main function for the program.
int main(int argc, char* argv[]) {
	
	//Making sure the right number of arguments have been given.
	if (argc != 2) {
		//If the right number of arguments hasn't been given, inform the user and return.
		cout << "Usage: ./trees numPoints" << endl;
		return 1;
	}
    
    //Number of points the user wanted
    const int numPoints = atoi(argv[1]);    

    //Making sure the number of points isn't 0
    if (numPoints == 0) {
        //If the number of points is 0, inform the user the tree is empty and return
        cout << "Tree is empty" << endl;
        return 2;
    }

	//Making sure the number of points the user wants is positive
	if (numPoints < 0) {
		//If the number of points isn't positive, inform the user and return.
		cout << "The number of points must be non-negative." << endl;
		return 2;
	}

	//Node for the head of the first tree
	node* head1 = new node;
      
    //Setting the X, Y, and Z values for the head
    cin >> head1->values[0];
    cin >> head1->values[1];
    cin >> head1->values[2];

	//Loop goes long enough to insert the number of points the user wanted - the head that was already created.
	for (int i = 1; i < numPoints; i++) {
        //Taking in the input for the new node's X, Y, and Z values
		int valuesForNewNode[3];
		cin >> valuesForNewNode[0];
		cin >> valuesForNewNode[1];
		cin >> valuesForNewNode[2];

		//Inserting the new node into the tree
		insertInTree(head1, valuesForNewNode, 0);
	}
 
	//Printing out the tree in a symmetric order.
	symmetricPrint(head1);

	//Node for the head of the second tree
	node* head2 = new node;

    //The head of the second tree is the same as the head of the first tree, since we are using pre-order traversal    
    head2->values[0] = head1->values[0];
    head2->values[1] = head1->values[1];
    head2->values[2] = head1->values[2];

    //Traversing the first tree in pre order and creating the second tree
	preOrderTraversal(head1, head2, true);

	//Printing out the second tree in post order
	postOrderPrint(head2);

	//The probe value the user wants to search for
	int probeValue;
	//Taking in the prove value from standard input
	cin >> probeValue;

	//Node for the last node encountered while searching the tree
	node* lastNodeEncountered;

	//Searching the tree and storing the last node encountered
	lastNodeEncountered = searchTree(head2, 1, probeValue);

	//Printing out the last node encountered while searching
	cout << "(" << lastNodeEncountered->values[0] << ", " << lastNodeEncountered->values[1] << ", " << lastNodeEncountered->values[2] << ")" << endl;

	return 0;
}


//Given: The head of the tree, the values for the new node, which value the tree is sorted by
//Returns: None
//Function inserts a new node into the tree, based on which value the tree is sorted by
void insertInTree(node* head, int newValues[], int basedOnWhich) {
	  
	//If the new value is less than or equal to the current head's value
	if (newValues[basedOnWhich] <= head->values[basedOnWhich]) {
        
        //If the current head doesn't have a left member
        if(head->left == 0){
            //Make a new node to the left of the current head
            head->left = new node;
            
            //Give the new node it's new values
            head->left->values[0] = newValues[0];
            head->left->values[1] = newValues[1];
            head->left->values[2] = newValues[2];
        }        
        
        //Otherwise if there is a left member
        else
            //Call insertInTree again using the current head's left member as the new head
            insertInTree(head->left, newValues, basedOnWhich);

        //Returning back to the previous recursion call, or out of the function      
        return;
	}

	//If the new value is greater than the current head's value
    if (newValues[basedOnWhich] > head->values[basedOnWhich]) {
        
        //If the current head doesn't have a right member
        if(head->right == 0){
            //Make a new node to the right of the current head
            head->right = new node;
            
            //Give the new node it's new values
            head->right->values[0] = newValues[0];
            head->right->values[1] = newValues[1];
            head->right->values[2] = newValues[2];
        }
        
        else
            insertInTree(head->right, newValues, basedOnWhich);

        //Returning back to the previous recursion call, or out of the function
		return;
	}

}

//Given: The head of the tree, which value the tree is sorted by, and the value being searched for
//Returns: The last node encountered while searching for the given search value
//Function searches the tree for a value the user gave, and returns either the node with that value or a node close to it
node * searchTree(node* head, int whichValue, int searchValue) {
	
    //Node that is either the closest in value to the search value or is identical    
    node* closestNode;    

    //If the current head's value is equal to the value being searched for
	if (head->values[whichValue] == searchValue)
		//Return the current head
		return head;

	//If the search value is less than the current head's value
	if (searchValue < head->values[whichValue]) {
		//If the current head has a node to the left
		if (head->left != 0)
			//Call searchTree again but look at the node to the left of the current head
			closestNode = searchTree(head->left, whichValue, searchValue);
		else
			//Otherwise if the node to the left doesn't exist, just return the current node
			return head;
	}

	//If the search value is greater than the current head's value
	if (searchValue > head->values[whichValue]) {
		//If the current head has a node to the right
		if (head->right != 0)
			//Call searchTree again but look at the node to the right of the current head
			closestNode = searchTree(head->right, whichValue, searchValue);
		else
			//Otherwise if the node to the right doesn't exist, just return the current node
			return head;
	}
    
    //Returning the closest node
    return closestNode;
}

//Given: The head of the tree being looked at
//Returns: None
//Function traverses the tree in symmetric order and prints each point
void symmetricPrint(node* head) {
	//If the node to the left of the current head exists
	if (head->left != 0)
		//Call symmetricPrint again but look at the node to the left of the current node
		symmetricPrint(head->left);

	//Print out the current node (point)
	cout << "(" << head->values[0] << ", " << head->values[1] << ", " << head->values[2] << ")" << endl;

	//If the node to the right of the current head exists
	if (head->right != 0)
		//Call symmetricPrint again but look at the node to the right of the current node
		symmetricPrint(head->right);
	
}

//Given: The head of the tree being traversed, the head of the second tree, and whether or not it's the first time this function has been called
//Returns: None
//Function traverses the first tree in pre order, and inserts each point into the second tree, which is sorted by the Y value.
void preOrderTraversal(node* head1, node* head2, bool firstRun ){
    //If this isn't the first time this function has been called
	if(!firstRun)
        //Inserting the current head of the first tree into the second tree, using the Y value to sort it
	    insertInTree(head2, head1->values, 1);

	//If the node to the left of the current node exists
	if (head1->left != 0) {
		//Call preOrderTraversal again but look at the node to the left of the current node
		preOrderTraversal(head1->left, head2, false);
	}

	//If the node to the right of the current node exists
	if (head1->right != 0) {
		//Call preOrderTraversal again but look at the node to the right of the current node
		preOrderTraversal(head1->right, head2, false);
	}
}

//Given: The head of the tree being looked at
//Returns: None
//Function traverses the tree in post order and prints each point
void postOrderPrint(node* head) {
	//If the node to the left of the current head exists
	if (head->left != 0)
		//Call postOrderPrint again but look at the node to the left of the current node
		postOrderPrint(head->left);

	//If the node to the right of the current head exists
	if (head->right != 0)
		//Call postOrderPrint again but look at the node to the right of the current node
		postOrderPrint(head->right);

	//Print out the current node (point)
	cout << "(" << head->values[0] << ", " << head->values[1] << ", " << head->values[2] << ")" << endl;
}
