//---------------------------------------------------------------------------
//Program name: genealogy.cpp
//Author: Bobby Bose
//Purpose: Implement a family tree using a graph structure.
//---------------------------------------------------------------------------

using namespace std;

//Compiler Directives
#include <vector>
#include <iostream>

//Struct for family vertex. Each family has a husband, wife, and children.
struct family_Vertex{
    int husband = 0;                                        //Husband of the family
    int wife = 0;                                           //Wife of the family
    vector<int> child;                                      //Vector of all the children of the family
    int numChildren = 0;                                    //How many children are in the family
};//family_Vertex

//Struct for person vertex. Each person belongs to two families. One through parents and one through marriage.
struct person_Vertex{
    int parents = 0;                                        //Parent family of the person
    int marriage = 0;                                       //Marriage family of the person
};//person_Vertex

//Struct for the nodes of the linkedList class.
struct node{
    int value = 0;                                          //Value of the node
    node* prev;                                             //Previous node in the list    
    node* next;                                             //Next node in the list
};//node

class linkedList{
    public:

        //Constructor
        linkedList(){
            head = 0;                                       //Head, rear, and size are all default to 0
            rear = 0;
            size = 0;
        }//linkedList()

        //Given: The value to enter
        //Returns: None
        //Purpose: Inserts a new value into a new node in the back of the list.
        void insert(int newValue){
            //Making a new node for the new word
            node* newNode = new node;
            //Giving the node it's value
            newNode->value = newValue;

            //If the list is empty
            if(size == 0){
                //The new node has no previous or next
                newNode->prev = 0;
                newNode->next = 0;
                //The new node is both the head and rear
                head = newNode;
                rear = newNode;
                //Increase the size of the list by one
                size += 1;
            }

            else{
                //Inserting the new node after the rear
                rear->next = newNode;
                //The new node's previous is the old rear
                newNode->prev = rear;
                //Making the new node the rear
                rear = newNode;
                //The new node has no next
                newNode->next = 0;
                //Increasing the size of the list by 1
                size += 1;
            }
        }//insert

        //Given: None
        //Return: The value being removed
        //Purpose: Removes a node from the front of the list
        int remove(){
            //Value of the node about to be removed
            int returnValue = head->value;
            //The head is now the next node
            head = head->next;
            //Decrease the size of the list by 1
            size -= 1;

            //Returning the removed value
            return returnValue;
        }//remove

        //Given: None
        //Returns: The head of the list
        //Purpose: Returns the head of the list
        node* getHead(){
            return head;
        }//getHead

        //Given: None
        //Returns: The size of the list
        //Purpose: Returns the size of the list
        int getSize(){
            return size;
        }//getSize

    private:
        node* head;                             //Head (Front) of the list
        node* rear;                             //Rear (Back) of the list
        int size;                               //Size of the list
};//linkedList


//Function prototypes
void stringSplit(string line, string words[], int &wordNum, person_Vertex* people[]);
void printStringArray(string words[], int numWords);
void personCommand(person_Vertex* people[], family_Vertex* families[], string words[]);
void familyCommand(person_Vertex* people[], family_Vertex* families[], string words[], int numWords);
void verifyCommand(person_Vertex* people[], family_Vertex* families[]);
void relateCommand(person_Vertex* people[], family_Vertex* families[], string words[]);
vector<pair<int,int>> BFS(person_Vertex* people[], family_Vertex* families[], int start, int end);


//Given: Arguments for the program
//Returns: None
//Purpose: Main program for the project
int main(int argc, char* argv[]){

    //Arrays for all the people and families. The max amount for each is 99
    person_Vertex* people[100];
    family_Vertex* families[100];

    //Initialize spots for all the people and vertices
    for(int i=0; i<100; i++){
        people[i] = new person_Vertex;
        families[i] = new family_Vertex;
    }

    //Variable for current line read in
    string currLine;

    //Until there are no more lines to read in
    while(getline(cin, currLine)){
        //String for all the words on the line. The max amount of words on a line is 26
        string wordsOnLine[26];
        //Variable for Number of words on the line
        int numberOfWords = 0;
        
        //Splitting the string into it's separate words
        stringSplit(currLine, wordsOnLine, numberOfWords, people);
        
        //If the first word on the line is person, call that command.
        if(wordsOnLine[0] == "Person"){
            personCommand(people, families, wordsOnLine);
        }

        //If the first word on the line is family, call that command.
        else if(wordsOnLine[0] == "Family"){
            familyCommand(people, families, wordsOnLine, numberOfWords);
        }

        //If the first word on the line is verify, call that command.
        else if(wordsOnLine[0] == "Verify"){
            verifyCommand(people, families);
        }

        //If the first word on the line is relate, call that command.
        else if(wordsOnLine[0] == "Relate"){
            relateCommand(people, families, wordsOnLine);
        }
    }

    //Returning from main
    return 0;

}//main

//Given: The current line read in, array to store the words in, number of words on the line, array of people
//Returns: None
//Purpose: Splits the line into separate words
void stringSplit(string line, string words[], int &wordNum, person_Vertex* people[]){
    //Variable for current full string
    string totalString = line;

    //Position in the string of the next space
    size_t spacePosition = totalString.find_first_of(" ");

    //Until there are no more spaces left
    while(spacePosition != string::npos){
        //Copy the current first word in the total string
        words[wordNum] = totalString.substr(0, spacePosition);
        //Cutting off the first word form the total string
        totalString = totalString.substr(spacePosition+1, totalString.length()-spacePosition-1);
        //Increase the total number of words by one
        wordNum += 1;
        //Position in the string of the next space
        spacePosition = totalString.find_first_of(" ");

    }

    //Adding the last word to the list of words
    words[wordNum] = totalString;
    //Increasing the number of words by one
    wordNum += 1;
    
}//stringSplit

//Given: The list of words, and number of words
//Returns: None
//Purpose: Prints the words out in an array. For testing purposes
void printStringArray(string words[], int numWords){
    //Cycling through all the words in the array and printing them out
    for(int i=0; i<numWords; i++){
        cout << words[i] << endl;
    }
}//printStringArray

//Given: The array of people, the array of families, and the words from the line.
//Returns: None
//Purpose: Adds a person vertex to the graph and potentially connects them to families
void personCommand(person_Vertex* people[], family_Vertex* families[], string words[]){
            //Current person being looked at
            int currPerson = stoi(words[1]);
            //Parent family of the person
            int parents = stoi(words[3]);
            //Marriage family of the person
            int marriage = stoi(words[5]);

            //Putting the parent family into the array
            people[currPerson]->parents = parents;
            //Putting the marriage family into the array
            people[currPerson]->marriage = marriage;

            //Printing out the person and their details
            cout << "Person " << currPerson << " has parents " << parents << " and is married in family " << marriage << "." << endl; 
}//personCommand

//Given: The array of people, the array of families, the words from the line, and the number of words on the line
//Returns: None
//Purpose: Adds a family vertex to the graph and potentially connects them to people
void familyCommand(person_Vertex* people[], family_Vertex* families[], string words[], int numWords){
    //Current family being looked at
    int currFamily = stoi(words[1]);
    //Husband of the current family
    int husband = stoi(words[3]);
    //Wife of the current family
    int wife = stoi(words[5]);

    //Adding the husband to the array of people
    families[currFamily]->husband = husband;
    //Adding the wife to the array of people
    families[currFamily]->wife = wife;

    //Printing out the first part of the family
    cout << "Family " << currFamily << " has husband " << husband << ", wife " << wife << ", and children";

    //Number of children in the family
    int numChild = (numWords-6)/2;

    //Cycling through the children
    for(int i=0; i<numChild-1; i++){
        //Taking in the person index for the child
        int childIndex = stoi(words[7 + (i*2)]);
        //Adding the child to the family's list of children
        families[currFamily]->child.push_back( childIndex );
        //Increasing the number of children in the family by one
        families[currFamily]->numChildren += 1;
        //Printing out the current child
        cout << " " << childIndex;
    }
            
    //Adding the last child       
    if(numChild != 0){
        //Adding the child to the family's list of children
        families[currFamily]->child.push_back( stoi(words[ 7 + ( (numChild-1) * 2) ]) );
        //Increasing the number of children in the family by one
        families[currFamily]->numChildren += 1;
        //Printing out the last child
        cout << " " << stoi(words[ 7 + ((numChild-1)*2) ]) << "." << endl;
    }
    else{
        //Print formatting
        cout << "."; 
        cout << endl;
    }

}//familyCommand


//Given: The array of people, the array of families
//Returns: None
//Purpose: Checks to see if all pointers from one type of vertex to the other also points back
void verifyCommand(person_Vertex* people[], family_Vertex* families[]){
    //Cycling through all the people
    for(int i = 1; i < 99; i++){
        //Family index for marriage
        int marriageOfPerson = people[i]->marriage;

        //Family index for parents
        int parentsOfPerson = people[i]->parents;

        //If the person points to parents
        if(parentsOfPerson != 0){
            //Variable for whether or not there is a back-pointer
            bool verified = false;

            //Cycling through all the children of the family
            for(int j=0; j<families[parentsOfPerson]->numChildren; j++){
                //If the child is pointed to by the family
                if(families[parentsOfPerson]->child[j] == i){
                    //Set verified to true
                    verified = true;
                }
            }

            //If there isn't a back-pointer
            if(verified == false){
                //Print it out
                cout << "Person " << i << " points to parent family " << parentsOfPerson << " but there is no back-pointer." << endl;
            }
        }

        //If the person points to a marriage
        if(marriageOfPerson != 0){
            //Variable for whether or not there is a back-pointer
            bool verified = false;

            //Cycling through all the children of the family
            for(int j=0; j<families[marriageOfPerson]->numChildren; j++){
                //If the child is pointed to by the family
                if(families[marriageOfPerson]->child[j] == i){
                    //Set verified to true
                    verified = true;
                }
            }

            //If there isn't a back-pointer
            if(verified != false){
                //Print it out
                cout << "Person " << i << " points to marriage family " << parentsOfPerson << " but there is no back-pointer" << endl;
            }
        }

    }

    //Cycling through all the families
    for(int i = 1; i < 99; i++){
        //Children of this family
        vector<int> children = families[i]->child;

        //Wife person index of this family
        int wifeIndex = families[i]->wife;

        //Husband person index of this family
        int husbandIndex = families[i]->husband;
        int childNum = families[i]->numChildren;

        //Checking if there is a husband
        if(husbandIndex != 0){
            //If the person doesn't point back to the family
            if(people[husbandIndex]->marriage != i){
                //Print it out
                cout << "Family " << i << " points to husband person " << husbandIndex << " but there is no back-pointer." << endl;
            }
        }

        //Checking if there is a wife
        if(wifeIndex != 0){
            //If the person doesn't point back to the family
            if(people[wifeIndex]->marriage != i){
                //Print it out
                cout << "Family " << i << " points to wife person " << wifeIndex << " but there is no back-pointer." << endl;
            }
        }

        //Cycling through all the children
        for(int j=0; j<childNum; j++){
            //Child's index in the people array
            int childIndex = children[j];

            //If The child doesn't point back to the family
            if(people[childIndex]->parents != i){
                //Print it out
                cout << "Family " << i << " points to child person " << childIndex << " but there is no back-pointer." << endl;
            }
        }

    }


}//verifyCommand

//Given: The array of people, the array of families, and the words from the line.
//Returns: None
//Purpose: Finds the path from one person to another and prints it out
void relateCommand(person_Vertex* people[], family_Vertex* families[], string words[]){
    //Retrieving the person to start at
    int start = stoi(words[1]);
    //Retrieving the person to end at
    int end = stoi(words[2]);

    //Contains every person or family from the start to the destination when using Breadth-First Search
    //Each pair is the current and next vertex (i.e. second came through first in BFS)
    vector<pair<int,int>> longPath  = BFS(people, families, start, end);

    //Vector for actual path from start to destination
    vector<int> path;
    //Adding the end to the path
    path.push_back(end);

    //Previous is the vertex that the last vertex added was pointed from
    int prev = longPath[longPath.size()-1].first;

    //Until the path has come back to the start
    while(prev != start){
        //Cycling through all the pairs retrieved from BFS
        for(size_t i = 0; i < longPath.size(); i++){
            //If the current pair is where previous came through
            if(longPath[i].second == prev){
                //Add prev to the path
                path.push_back(prev);
                //The vertex the old previous came through is now the new previous
                prev = longPath[i].first;
                //Breaking out of the for loop, since we already found the pair.
                break;
            }

        }
    }

    //For print formatting
    cout << "person " << start;

    //Going backwards through the path vector (forwards in the actual path)
    for(int i = path.size()-1; i >= 0; i--){
        //For print formatting
        cout <<  " -> ";

        //If the current vertex is a family
        if(path[i] > 100){
            //Print it out
            cout << "family " << path[i]-100;
        }
        //Otherwise the current vertex is a person
        else{
            //Print it out
            cout << "person " << path[i];
        }
        
    }

    //For print formatting
    cout << endl;


}//relateCommand

//Given: The array of people, the array of families, the start index, and the end index
//Returns: The pairs of vertices looked at in the BFS
//Purpose: Finds the path from one vertex to another. Stores this information and returns it
vector<pair<int,int>> BFS(person_Vertex* people[], family_Vertex* families[], int start, int end){
    //Determines if a vertex has been visited.
    //1-99 are people. 101-199 are families
    bool visited[200];

    //Setting all vertex's visited status to false
    for(int i = 0; i < 200; i++){
        visited[i]=false;
    }

    //
    visited[0] = true;
    visited[100] = true;


    //In the queue, people are 1-99, families are 101-199
    linkedList* Queue = new linkedList();
   
    //Vertices looked at in BFS. Each pair is the current and next vertex.
    vector<pair<int, int>> path;

    //The start has been visited since we start there
    visited[start] = true;
    //Inserting the start vertex into the queue
    Queue->insert(start);

    //Until the queue is empty
    while(Queue->getHead() != 0){
        //Remove the first element from the queue
        int place = Queue->remove();

        //If the current vertex is a person
        if(place < 100){
            //Family index for the parent of the vertex
            int parent = people[place]->parents + 100;
            //Family index for the marriage of the vertex
            int marriage = people[place]->marriage + 100;                

            //If the parent exists and has not been visited
            if( (parent != 100) && (visited[parent] == false) ){
                //Indicate that they now have been visited
                visited[parent] = true;
                //Create a new pair for this person and family
                pair<int, int> temp  (place, parent);
                //Insert the pair into the vector
                path.push_back(temp);
                //Add the parent to the end of the queue
                Queue->insert(parent);
            }
            
            //If the marriage exists and has not been visited
            if( (marriage != 100) && (visited[marriage] == false) ){
                //Indicate that they now have been visited
                visited[marriage] = true;
                //Create a new pair for this person and family
                pair<int, int> temp  (place, marriage);
                //Insert the pair into the vector
                path.push_back(temp);
                //Add the marriage to the end of the queue
                Queue->insert(marriage);
            }
        }

        //Otherwise, the current vertex is a family
        else{
            //Person index for the husband of the family
            int husband = families[place-100]->husband;
            //Person index for the wife of the family
            int wife = families[place-100]->wife;
            //Vector for the children of the family
            vector<int> children = families[place-100]->child;

            //If the husband exists and hasn't been visited
            if( (husband != 0) && (visited[husband] == false) ){
                //Indicate that they now have been visited
                visited[husband] = true;
                //Create a new pair for this family and person
                pair<int, int> temp  (place, husband);
                //Insert the new pair into the vector
                path.push_back(temp);
                //Add the husband to the end of the queue
                Queue->insert(husband);
                
                //If the husband is the destination
                if(husband == end){
                    //Return the vector of pairs
                    return path;
                }
            }
            
             //If the wife exists and hasn't been visited
             if( (wife != 0) && (visited[wife] == false) ){
                //Indicate that they now have been visited
                visited[wife] = true;
                //Create a new pair for this family and person
                pair<int, int> temp  (place, wife);
                //Insert the new pair into the vector
                path.push_back(temp);
                //Add the wife to the end of the queue
                Queue->insert(wife);

                //If the wife is the destination
                if(wife == end){
                    //Return the vector of pairs
                    return path;
                }
            }

            //Cycling through the children in the family
            for(int i=0; i<families[place-100]->numChildren; i++){
                //If the child hasn't been visited
                if(visited[children[i] == false]){
                    //Indicate that they now have been visited
                    visited[children[i]] = true;
                    //Create a new pair for this family and person
                    pair<int, int> temp  (place, children[i]);
                    //Insert the new pair into the vector
                    path.push_back(temp);
                    //Add thechild to the end of the queue
                    Queue->insert(children[i]);

                    //If the current child is the destination
                    if(children[i] == end){
                        //Return the vector of pairs
                        return path;
                    }//if
                }//if
            }//for    

        }//else


    }//while

    return path;

}//BFS
