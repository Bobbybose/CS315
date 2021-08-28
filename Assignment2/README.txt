Assignment 2: Trees
Author: Bobby Bose
Makefile code provided by Dr. Finkel. Edited by Bobby Bose to properly zip README.txt.

Instructions on compiling: Type in "make run" into the command line to compile and run the program.
Output is pushed into a file named tmpRun.out

Purpose of this program is to simulate a binary tree in C++. Each tree has a parent node, and a left and right node, which in turn can act as a parent node and have its own left and right nodes, and so on.
Each node consists of three data values, X, Y, and Z. The nodes are meant to simulate points.

The program takes in one parameter to determine have many data points are in the tree.
It then reads in n points from standard input. In this program, we use the randGen perl script to obtain our data.
These points are placed into a binary tree T1, which is sorted based on the X value of the points. Ties are resolved by going to the left.
T1 is then traversed in symmetric order, and each point is printed out.
T1 is then traversed in preorder, and each node is placed into a new, initially empty, tree T2. This tree is sorted by its Y value. Ties again are resolved by going to the left.
T2 is then traversed in postorder, and each point is printed out.
Finally, one more integer is read from standard input, and T2 is searched for this point, looking at the Y values. The last node encountered (which might have the searched value itself) is printed.

