//---------------------------------------------------------------------------
//Program name: kd.cpp
//Author: Bobby Bose
//Purpose: Program creates a 4-dimensional k-d tree using user input and searches for probes
//---------------------------------------------------------------------------

//Compiler Directives
#include <iostream>							//Needed for cout/cin
#include <vector>							//Used for the buckets and points

using namespace std;

//Struct for the nodes that make up the tree
struct node {
	node* left;								//Points to left child
	node* right;							//Points to right child
		
	int dimension;							//Which dimension to discriminate on. Only internal nodes have a value for this.		
	int discrimValue;						//Which value to discriminate on. Only internal nodes have a value for this.

	vector<vector<int>> bucket;				//Points and their values. Only leaf nodes have values inside them.	
};


//Function prototypes
void build_tree(vector<vector<int>> points, node* currTop);
int getMax(vector<vector<int>> values, int dimensionValue);
int getMin(vector<vector<int>> values, int dimensionValue);
int getRange(vector<vector<int>> values, int dimensionValue);
int determineDiscriminateDimension(vector<vector<int>> values);
int partition(vector<vector<int>> &points, int dimension, int low, int high);
int quickSelect(vector<vector<int>> &points, int dimension, int first, int last, int searchSmallest);
void printTree(node* head);
void printPoint(vector<int> point);
void printBucket(vector<vector<int>> bucket);
vector<vector<int>> probeSearch(node* head, vector<int> probePoint);

//Number of dimensions for the k-d tree. For this project dimension is 4.
const int NUM_DIMENSIONS = 4;


//Given: Arguments for the program
//Returns: None
//Main program for the project
int main(int argc, char* argv[]) {

	//Making sure the right number of arguments have been given.
	if (argc != 3) {
		//If the right number of arguments hasn't been given, inform the user and return.
		cout << "Usage: ./kd pointCount probeCount" << endl;
		return 1;
	}

	//How many points are in the tree
	int pointCount = atoi(argv[1]);
	
	//How many points the user wants to probe for
	int probeCount = atoi(argv[2]);

	//Making sure the number of points is not negative
	if (pointCount < 0) {
		//If the number of points is negative, inform the user and return
		cout << "Number of points cannot be negative" << endl;
		return 2;
	}

	//Making sure the number of probes is not negative
	if (probeCount < 0) {
		//If the number of probes is negative, inform the user and return
		cout << "Number of probes cannot be negative" << endl;
		return 2;
	}

	//Node for the head of the tree
	node* head = new node;
	
	//All the points in the tree
	vector<vector<int>> allPoints;

	//Used to temporarily read in data before pushing into vector
	int readValue;

	//Adding all the values into the points
	for (int i = 0; i < pointCount; i++) {
		
		//Used to temporarily hold values for new points before inserting into bigger list of points.
		vector<int> newValues;

		//Cycling through for all dimension points
		for (int j = 0; j < NUM_DIMENSIONS; j++) {
			//Reading in a value
			cin >> readValue;
			//Pushing the new value onto the new point
			newValues.push_back(readValue);
		}

		//Pushing the new point onto the list of points
		allPoints.push_back(newValues);
	}

	//Building the tree
	build_tree(allPoints, head);

	//List of points to probe for in the tree.
	vector<vector<int>> probePoints;

	//Cycling through the number of probes
	for (int i = 0; i < probeCount; i++) {

		//Used to temporarily hold values for new probe points before inserting into bigger list of points
		vector<int> newValues;

		//Cycling through for all dimension points
		for (int j = 0; j < NUM_DIMENSIONS; j++) {
			//Reading in a value
			cin >> readValue;
			//Pushing the new value onto the new probe
			newValues.push_back(readValue);
		}

		//Pushing the new probe point onto the list of probes
		probePoints.push_back(newValues);
	}

	//Cycling through the list of probes
	for (int i = 0; i < probeCount; i++) {
		//Printing out the probe point
		cout << "probe ";
		printPoint(probePoints.at(i));
		cout << "reaches bucket: ";

		//Finding the bucket the probe would fall into
		vector<vector<int>> probeResult = probeSearch(head, probePoints.at(i));

		//Printing out the number of elements in the bucket
		cout << probeResult.size() << " elements" << endl;

		//Printing the bucket that the probe point would fall into if sorted in.
		printBucket(probeResult);
	}

}//main


//Given: The list of points needed to be split, and the current node that is being looked at
//Returns: None
//Builds the k-d tree using discriminate values based on the dimension ranges. More information is in the README.
void build_tree(vector<vector<int>> points, node *currTop) {

	//If the amount of points left to look at is less than 10
	if (points.size() <= 10) {
		//This node is a leaf node so it needs a bucket
		currTop->bucket = points;
		//Return since there is no more need for leaves on this branch
		return;
	}

	//Getting the dimension to discriminate on for this node
	int discrimDimension = determineDiscriminateDimension(points);

	//Setting the current node's dimension value
	currTop->dimension = discrimDimension;

	//Median value to divide the points around
	int median;
	//Left end of the points given to the left node
	int leftEnd;
	//Right start of the points given to the right node
	int rightStart;
	//How many points are in the current list of points
	int sizeOfPoints = points.size();

	//If there is an even number of points
	if (points.size() % 2 == 0) {
		//Doing some math to figure out the median, left point list end, and right point list start
		median = sizeOfPoints / 2 - 1;
		leftEnd = sizeOfPoints / 2;
		rightStart = sizeOfPoints / 2;
	}
	//If there is an odd number of points
	else {	
		//Doing some math to figure out the median, left point list end, and right point list start
		median = sizeOfPoints / 2;
		leftEnd = sizeOfPoints / 2 + 1;
		rightStart = sizeOfPoints / 2 + 1;
	}

	//What value to discriminate on in the list of points.
	int discriminantValue = quickSelect(points, discrimDimension, 0, sizeOfPoints-1, median);
	
	//Setting the current node's dimension value
	currTop->discrimValue = discriminantValue;


	//Points to be given to the left node to look through
	vector<vector<int>> newPointsLeft;

	//Looping through the points that are to be given to the left node
	for (int i = 0; i < leftEnd; i++) {

		//Temporarily holds the dimension values for the new point
		vector<int> newValuesTemp;

		//Cycling through all the dimensions
		for (int j = 0; j < NUM_DIMENSIONS; j++) {
			//Adding the new dimension value into the new point
			newValuesTemp.push_back(points.at(i).at(j));
		}

		//Pushing the new point onto the list of new points
		newPointsLeft.push_back(newValuesTemp);
	}

	//Left node of the current node
	node* leftChild = new node;
	//Setting the current node's left child variable
	currTop->left = leftChild;
	//Calling build_tree again using the left node and the new list of points.
	build_tree(newPointsLeft, leftChild );


	//Points to be given to the right node to look through
	vector<vector<int>> newPointsRight;

	//Looping through the points that are to be given to the right node
	for (int i = rightStart; i < sizeOfPoints; i++) {

		//Temporarily holds the dimension values for the new point
		vector<int> newValuesTemp;

		//Cycling through all the dimensions
		for (int j = 0; j < NUM_DIMENSIONS; j++) {
			//Adding the new dimension value into the new point
			newValuesTemp.push_back(points.at(i).at(j));
		}

		//Pushing the new point onto the list of new points
		newPointsRight.push_back(newValuesTemp);
	}

	//Right node of the current node
	node* rightChild = new node;
	//Setting the current node's right child variable
	currTop->right = rightChild;
	//Calling build_tree again using the right node and the new list of points.
	build_tree(newPointsRight, rightChild);


}//build_tree


//Given: A list of points, the dimension to look at
//Returns: The largest value in the dimension requested of the points being looked at
//Finds the max value in a set of given points using the dimension value provided
int getMax(vector<vector<int>> values, int dimensionValue) {
	//Variable to hold the largest value
	int largestValue = -1;
	
	//Cycling through all the points
	for (int i = 0; i < values.size(); i++) {
		//If the current value being looked at is bigger than the current largest value
		if (largestValue < values.at(i).at(dimensionValue))
			//Current value is the new largest value
			largestValue = values.at(i).at(dimensionValue);
	}
	
	//Returning the largest value
	return largestValue;
}//getMax


//Given: A list of points, the dimension to look at
//Returns: The smallest value in the dimension requested of the points being looked at
//Finds the min value in a set of given points using the dimension value provided
int getMin(vector<vector<int>> values, int dimensionValue) {
	//Variable to hold the smallest value
	int smallestValue = 10000;

	//Cycling through all the points
	for (int i = 0; i < values.size(); i++) {
		//If the current value being looked at is smaller than the current smallest value
		if (smallestValue > values.at(i).at(dimensionValue))
			//Current value is the new smallest value
			smallestValue = values.at(i).at(dimensionValue);
	}

	//Returning the smallest value
	return smallestValue;
}//getMin


//Given: A list of points, the dimension to look at
//Returns: The range of the values in the given dimension of the given points
//Finds the range of the given values in the given dimension, using the getMax and getMin functions
int getRange(vector<vector<int>> values, int dimensionValue) {
	//Range is the max-min
	int range = abs(getMax(values, dimensionValue) - getMin(values, dimensionValue));
	
	//Returning the range
	return range;
}//getRange


//Given: A list of points
//Returns: The largest range
//Finds which dimension of a list of points has the largest range
int determineDiscriminateDimension(vector<vector<int>> values) {
	
	//Variable for the index of the largest range
	int indexOfGreatestRange;

	//Variable for the largest range
	int greatestRange = -1;

	//Cycling through the dimensions of the points
	for (int i = 0; i < NUM_DIMENSIONS; i++) {
		
		//What the current range being looked at is
		int currRange = getRange(values, i);
		//If the current range is larger than the previously largest range
		if ( currRange > greatestRange) {
			//Record the current index
			indexOfGreatestRange = i;
			//Record the new largest range
			greatestRange = currRange;
		}

	}

	//Returning the largest range
	return indexOfGreatestRange;

}//determineDiscriminateDimension


//Given: Vector of points, dimension to look at, low index to search from, high index to search to
//Returns: A place to start the pivot for the QuickSelect algorithm
//Uses last element as pivot. Places pivot element in correct spot in vector and rearranges so all elements smaller are on the left
//	and elements bigger are on the right.
int partition(vector<vector<int>> &points, int dimension, int low, int high) {

	//Setting the pivot to the last value in the list of points
	int pivotValue = points.at(high).at(dimension);

	//Index of the small element
	int index = (low - 1);

	//Moving through the vector of points
	for (int i = low; i <= high - 1; i++)
	{

		//If the dimension value of the current point being looked at is smaller than or equal to the pivot
		if (points.at(i).at(dimension) <= pivotValue){
			//The smaller element index moves up one
			index += 1;
			//Swapping the smaller point and the current point being looked at
			swap(points[index], points[i]);
		}
	}

	//Swapping the point after the last small point looked at, and the last point in the list.
	swap(points[index + 1], points[high]);

	//Returning the Index after the last small point
	return (index + 1);
}//partition


//Given: A list of points, the dimension to look at, the low and high indicies in the list of points to look at, and the lookingValue'th largest element to return
//Returns: The lookingValue'th largest element in the list of points
//Sorts the array enough to find the lookingValue'th smallest point in the list of points
int quickSelect(vector<vector<int>> &values, int dimension, int low, int high, int lookingValue){
	//Making sure there are at least lookingValue number points, and that it can fit in the range
	if (lookingValue + 1 > 0 && lookingValue <= high - low ) {

		//Using the partition function to find a starting pivot	
		int index = partition(values, dimension, low, high);

		//If the index is the same as lookingValue's
		if (index - low == lookingValue)
			//Return the current index's value
			return values.at(index).at(dimension);

		//If the index is more than lookingValue's
		if (index - low > lookingValue)
			//Recurse on the left subset of points
			return quickSelect(values, dimension, low, index - 1, lookingValue);

		//Otherwise index is more than lookingValue, and program needs to recurse on the right subset of points
		return quickSelect(values, dimension, index + 1, high, lookingValue - index + low - 1);
	}

	//If lookingValue is larger than the number of elements in the array
	return -1;
}//quickSelect



//USED FOR TESTING PURPOSES
//Given: the head of the tree to print
//Returns: None
//Prints out the tree based from the given head
void printTree(node *head) {

	//If the current head has a left node
	if (head->left != 0)
		//Recurse on that left node
		printTree(head->left);

	//If the node is a leaf
	if ((head->left == 0) && (head->right == 0) ) {
		//Print out the size of the tree
		cout << "Size:  " << head->bucket.size() << endl;

		//Cycles through the number of points
		for (int i = 0; i < head->bucket.size(); i++) {
			cout << "(";
		
			//Cycles through the number of dimensions
			for (int j = 0; j < NUM_DIMENSIONS; j++) {
				//Prints one dimension value at a time
				cout << head->bucket.at(i).at(j) << ",";
			}
			
			cout <<  ")    ";
		}

		cout << endl;
	}

	//If the current head has a right node
	if (head->right != 0)
		//Recurse on that right node
		printTree(head->right);


}//printTree


//Given: A point to print
//Returns: None
//Prints out a singular point
void printPoint(vector<int> point){
	//Cycling through the point's dimensions
	for (int i = 0; i < point.size(); i++) {
		//Printing out one dimension value at a time
		cout << point.at(i) << " ";
	}
}//printPoint


//Given: A bucket to print
//Returns: None
//Prints out the points in a bucket
void printBucket(vector<vector<int>> bucket) {
	//Cycling through the points in the bucket
	for (int i = 0; i < bucket.size(); i++) {
		//Printing out the current point
		printPoint(bucket.at(i));
		cout << endl;
	}
}//printBucket


//Given: The head of the tree, and the point to probe for
//Returns: the bucket of the leaf the probe point would fall into
//Probes the tree to find which bucket a given probe point would fit into.
vector<vector<int>> probeSearch(node *head, vector<int> probePoint) {
	//If the current node is a leaf
	if ((head->left == 0) && (head->right == 0)) {
		//Return with the leaf's bucket of points
		return head->bucket;
	}

	//Dimension of the current head
	int currDimension = head->dimension;

	//If the probe is greater than the discriminant value
	if (head->discrimValue < probePoint.at(currDimension))
		//Recurse on the right child
		return probeSearch(head->right, probePoint);

	//If the probe is smaller than the discriminant value
	if (head->discrimValue >= probePoint.at(currDimension)) 
		//Recurse of the left child
		return probeSearch(head->left, probePoint);

	//This part is here to remove a warning form gcc about potentially not being able to return from
	//	this function because all returns are in if statements.
	vector<vector<int>> useless;
	return useless;
}//probeSearch
