Assignment 1: Deck of Dequeues
Author: Bobby Bose
Makefile code provided by Dr. Finkel, and edited by Bobby Bose

Instructions on compiling: Type in "make run" into the command line to compile and run the program.
Output is pushed into a file named tmpRun.out

Makefile code was edited to compile linkedList.h and linkedList.cpp, as well as cleaning and zipping the proper files.

Purpose of this program is to simulate the card game described in the assignment page. 
N players are given a deck of cards, numbered 1 to c, with c being given by the program user. 
Each card has a weight of d*v, where d is the depth of the card in the stack of cards, and v is the card's value. 

Every turn, an n-sided dice is rolled which determines which player gives up a card that turn. 
A 2-sided dice is rolled then determining if the player gives up a card form the bottom or top of their deck (1 being top and 2 being bottom). 
Another n-sided dice is rolled, which determines which player recieves the card. 
This can be the same player as the one giving away a card. 
The recieving player puts the card on top of their pile.

The first player to have an empty deck wins. If the maximum number of turns is reached, then the lowest-numbered player with the lowest weighted deck wins.
