Assignment 3: Word Counter
Author: Bobby Bose
Makefile code provided by Dr. Finkel. Edited by Bobby Bose to properly zip README.txt, my own test data, and the output on that test data
NOTE: Dr. Finkel's notes were used as reference in the writing of quick sort and merge sort.

Extra Credit: I implemented more than one sorting method, merge sort and quick sort. They are both used in the program, for the two different ways of sorting.

Own test data: My own provided test data contains part of the first chapter of The Lord of the Rings: the Fellowship of the Ring  

Instructions on compiling: Type in "make run" into the command line to compile and run the program.
Output is pushed into a file named tmpRun.out
NOTE: When compiling, a warning is received about comparing signed and unsigned numbers. I was not sure how to fix this error, as I have no experience dealing
      with signed and unsigned numbers in C++.

Purpose of this program is to keep a record of all the words in a given data file, and to also record how often each word appears in the text.
This data is outputted in two ways. The first output is sorted by word in alphabetical order. 
The second output is sorted in decreasing number of occurrences, with ties being sorted in increasing alphabetical order.
A word in this program is any set of non-space characters. This includes special symbols and punctuation.

This program takes in one parameter: the data file to be read.
The program first reads in each word and inserts it into a hash table. This hash table uses external chaining, using a linked list. 
Each node in the linked list keeps track of the word, how often the word occurs, and the next node in the linked list.

The nodes are then extracted from the list, and first sorted in alphabetical order using merge sort. 
After it is sorted, the words and their occurrence count are printed.

The nodes are then sorted in decreasing order of count using quick sort and Lomuto's partitioning method.
After it is sorted, the words and their occurrence count are again printed.