//---------------------------------------------------------------------------
//Program name: wordCount.cpp
//Author: Bobby Bose
//Purpose: Count the number of words in a text file and output in a couple ways to display the information
//---------------------------------------------------------------------------


//Compiler Directives
#include <iostream>

using namespace std;

//Struct used for each word. Needed because a count of occurrences is needed.
struct node{
    string word;                            //Word value from the read data
    int count;                              //How many times the word appears in the text
    node* next;                             //Points to the next node in the linked list.
};//node

//Singly linked list class
class linkedList{
    public:
        
        //Constructor
        linkedList(){
            head = 0;                       //Head defaults to 0 (NULL)
        }//linkedList()


        //Given: The word to enter
        //Returns: None
        //Purpose: Inserts the new word into a new node in the front, if the word isn't already present.
        //         If the word is already present, then the count variable in that word's node is just incremented by one. 
        void insert(string newWord){
            //curr starts at the front of the linked list
            node* curr = head;

            //Until the end of the linked list is reached
            while(curr != 0){
                //If the current node's word is the same as the word we're looking for
                if(curr->word == newWord){
                    //Increment count by 1 and return
                    curr->count += 1;
                    return;
                }

                //Moving forward to the next node
                curr = curr->next;                
            }

            //Making a new node for the new word
            node* newNode = new node;
            //Adding the word to the node
            newNode->word = newWord;
            //Setting the node's count to 1
            newNode->count = 1;
            
            //If the linked list is empty
            if(head == 0)
                //Set the new node's head to NULL
                newNode->next = 0;
            else
                //Otherwise if the list isn't empty, make the new node's next the current head
                newNode->next = head;   
            
            //Set the new node to the head
            head = newNode;
        }

        //Given: None
        //Return: The head of the linked list
        //Purpose: Returns the head of the linked list.
        node* getHead(){
            return head;
        }//insert


    private:
        node* head;         //Head (Front) of the linked list

};//linkedList

//Function prototypes
int hashFunction(string word);
void printHashTable(linkedList words[]);
int getNumWords(linkedList words[]);
void readingFile(linkedList hashT[]);
void readingHashTable(node* wordList[], linkedList hashT[]);
void mergeSort(node* words[], int low, int high);
void merge(node* words[], int low, int high);
void printWords(node* words[], int length);
void quickSort(node* words[], int low, int high);
int partition(node* words[], int low, int high);

//What the value for the mod function in the hash function is
const int HASH_TABLE_LENGTH = 17;


//Given: Arguments for the program
//Returns: None
//Purpose: Main program for the project 
int main(int argc, char* argv[]){

    //Hash table that the nodes (words) are going to be in
    linkedList hashTable[HASH_TABLE_LENGTH];
    
    //Reading the words form the given text file
    readingFile(hashTable);

    //How many words are in the file
    int wordCount = getNumWords(hashTable);

    //Array of all the nodes in the hash table.
    node* words[wordCount];

    //Reading the data from the hash table into the array
    readingHashTable(words, hashTable);

    //Sorting the words in alphabetical order
    mergeSort(words, 0, wordCount-1);

    //Printing out the alphabetically sorted list
    printWords(words, wordCount);

    //Sorting the words in reverse numerical order
    quickSort(words, 0, wordCount-1);

    //Adding a space between the two outputs
    cout << endl;

    //Printing out the reverse numerically sorted list
    printWords(words, wordCount);

    //Returning from main
    return 0;
}//main


//Given: Word to put into hash function
//Returns: Index value for word in hash table
//Purpose: Hash function to sort words into a hash table
//         Function adds alphabet character position values for each letter in the word, and then mods it by the hash table length
int hashFunction(string word){
    //Total weight of the letters in the word
    int wordWeight = 0;

    //Cycling through each letter in the word
    for(int i = 0; i<=word.length(); i++){
        //Adding the current letter's weight to the total.
        wordWeight += (i & 31);
    }

    //Returning the hash table index value
    return (wordWeight % HASH_TABLE_LENGTH);


}//hashFunction


//Given: The hash table, which is an array of linkedLists
//Returns: None
//Purpose: Prints the hash table, starting from the first index, and the beginning of each linkedList.
//         Used for testing
void printHashTable(linkedList words[]){
    //Cycling through the hash table indices
    for(int i=0; i<HASH_TABLE_LENGTH; i++){
        cout << "Index " << i << ": ";

        //Starting at the front of the linkedList
        node* curr = words[i].getHead();

        //Until the end of the linkedList is reached
        while(curr != 0){

            //Printing the current word
            cout << curr->word << " ";

            //Moving to the next node in the list
            curr = curr->next;
        }
        cout << endl << endl;
    }
}//printHashTable


//Given: The hash table, which is an array of linkedLists
//Returns: How many words are in the hash table
//Purpose: Counts the number of words in the hash table
int getNumWords(linkedList words[]){
    //Variable for the number of words
    int numWords = 0;

    //Cycling through the hash table indices
    for(int i=0; i<HASH_TABLE_LENGTH; i++){

        //Starting at the front of the linkedList
        node* curr = words[i].getHead();

        //Until the end of the linkedList is reached
        while(curr != 0){

            //Incrementing the number of words by one
            numWords += 1;

            //Moving on to the next word in the list
            curr = curr->next;
        }
    }

    //Returning the number of words
    return numWords;
}//getNumWords


//Given: The hash table, which is an array of linkedLists
//Returns: None
//Purpose: Reads the words in from the data file of inserts it into the hash table
void readingFile(linkedList hashT[]){
    //Variable for the current word being looked at 
    string currWord;

    //Variable for the index in the hash table being looked at
    int indexForNewWord;

    //Until there are no more words to read in
    while(cin >> currWord){
        //Using the hash function to find the index for the current word
        indexForNewWord = hashFunction(currWord);
        
        //Inserting the new word into the hash table
        hashT[indexForNewWord].insert(currWord);
    }

}//readingFile


//Given: The list of nodes, and the hash table
//Returns: None
//Purpose: Reads the hash table, and inserts the data into a new array of nodes
void readingHashTable(node* wordList[], linkedList hashT[]){
    //Variable keeps track of the next open index in the array of nodes
    int wordListPos = 0;
 
    //Cycling through the hash table
    for(int i=0; i< HASH_TABLE_LENGTH; i++){
        //Starting at the head of the linkedList
        node* curr = hashT[i].getHead();

        //Until the end of the list is reached
        while(curr != 0){
            //Inserting the current node into the new array of nodes
            wordList[wordListPos] = curr;

            //Moving up the current position in the array of nodes by one
            wordListPos += 1;

            //Moving on to the next node in the linkedList
            curr = curr->next;
        }

    }

}//readingHashTable


//Given: The array of nodes, the first index in the array to look at, the last index in the array to look at
//Returns: None
//Purpose: Sorts the nodes in alphabetical order using the merge sort algorithm
void mergeSort(node* words[], int low, int high){
    //If the low and high indices are equal or have crossed each other, then return
    if(high <= low)
        return;
    
    //Mid is midway point in the subarray
    int mid = (low+high)/2;

    //Recursing on the left subarray
    mergeSort(words, low, mid);
    
    //Recursing on the right subarray
    mergeSort(words, mid+1, high);

    //Remerging the subarrays
    merge(words, low, high);

}//mergeSort


//Given: The array of nodes, the first index in the array to look at, the last index in the array to look at
//Returns: None
//Purpose: Re-merges the two subarrays and sorts them in alphabetical order
void merge(node* words[], int low, int high){
    //Midpoint is the middle of the subarray
    int mid = (low+high)/2;

    //Sizes for the two temporary arrays
    int sizeL = mid-low+1;
    int sizeH = high-mid;

    //Temporary Arrays for the left and right side of the midpoint
    node* lowerArray[sizeL];
    node* upperArray[sizeH];


    //Populating the left subarray with it's values from the given array
    for(int i=0; i< sizeL; i++){
        lowerArray[i] = words[i+low]; 
    }

    //Populating the right subarray with it's values from the given array
    for(int i=0; i< sizeH; i++){
        upperArray[i] = words[mid+1+i];
    }

    //Where we are in the left subarray
    int currIndexL = 0;

    //Where we are in the right subarray
    int currIndexR = 0;

    //Where in the main array we are. Starts where the merged array starts
    int arrayPos = low;

    //Until one of the subarrays has reached it's end
    while(currIndexL < sizeL && currIndexR < sizeH){

        //If the word in the left subarray is smaller than the word in the right subarray
        if(lowerArray[currIndexL]->word <= upperArray[currIndexR]->word){
            //Add this node to the array
            words[arrayPos] = lowerArray[currIndexL];
           
            //Increment position in the left subarray by one
            currIndexL += 1;
        }
        //Otherwise, word in right subarray is smaller
        else{
            //Add this node to the array
            words[arrayPos] = upperArray[currIndexR];
           
            //Increment position in the right subarray by one
            currIndexR += 1;
        }

        //Increment position in the main array by one
        arrayPos += 1;

    }

    //Until there are no more elements in the left subarray
    while(currIndexL < sizeL){
        //Add current node to the main array
        words[arrayPos] = lowerArray[currIndexL];

        //Increment position in the left subarray by one
        currIndexL += 1;

        //Increment position in the main array by one
        arrayPos += 1;
    }

    //Until there are no more elements in the right subarray
    while(currIndexR < sizeH){
        //Add the current node to the main array
        words[arrayPos] = upperArray[currIndexR];

        //Increment position in the right subarray by one
        currIndexR += 1;

        //Increment position in the main array by one
        arrayPos += 1;
    }

}//merge


//Given: The array of nodes, the first index in the array to look at, the last index in the array to look at
//Returns: None
//Purpose: Sorts the given array in reverse numerical order. Ties use the word and sort in alphabetical order
void quickSort(node* words[], int low, int high){
    //If the low and high indices become equal or cross, return
    if(high <= low)
        return;

    //Mid point if found using the partition method
    int mid = partition(words, low, high);

    //Recursing on the left subarray
    quickSort(words, low, mid-1);

    //Recursing on the right subarray
    quickSort(words, mid+1, high);

}//quickSort


//Given: The array of nodes, the first index in the array to look at, the last index in the array to look at
//Returns: The index of the node to pivot around
//Purpose: Partitions the array into two subarrays, with all elements smaller than the pivot on the left, and all elements
//         larger than the pivot on the right
int partition(node* words[], int low, int high){
    //Using the first element in the array as the pivot
    node* pivot = words[low];

    //Variable for the index of the pivot. Array divides around this index
    int indexD = low;

    //Looping through the array. Starts at the element after the pivot
    for(int i = low+1; i<=high; i++){

        //If the current indice's count is larger than the pivot's count
        if(words[i]->count > pivot->count){
            //Move the pivot up one in the array
            indexD += 1;

            //Swap the pivot with the current index's node
            swap(words[indexD], words[i]);
        }

        //If the current indice's count is equal to the pivot's count
        else if(words[i]->count == pivot->count){
            //Compare the words, and if the current word is smaller than the pivot's word
            if(words[i]->word < pivot->word){
                //Move the pivot up one in the array
                indexD += 1;

                //Swap the pivot with the current index's node
                swap(words[indexD], words[i]);
            }
        }
    }

    //Make one final swap with the pivot and the element at the beginning
    swap(words[indexD], words[low]);

    //Returning the index to divide the array on
    return indexD;

}//partition


//Given: The array of nodes, and the length of the array
//Returns: None
//Purpose: Prints out all the words in the text, and how often they occur
void printWords(node* words[], int length){
    //Looping through the array of nodes
    for(int i = 0; i < length; i++){
        //Printing ou the word and it's count on the same line
        cout << words[i]->word << " " << words[i]->count << endl;
    }
}//printWords