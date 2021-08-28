Assignment 3: K-D Trees
Author: Bobby Bose
Makefile code provided by Dr. Finkel. Edited by Bobby Bose to properly zip README.txt and for testing purposes

Instructions on compiling: Type in "make run" into the command line to compile and run the program.
Output is pushed into a file named tmpRun.out
NOTE: When compiling, some warnings are recieved about comparing signed and unsigned numbers. I was not sure how to fix these errors, as I have no experience dealing with signed and unsigned numbers in C++.
      The program will still function properly despite this.


Purpose of this program is to simulate a K-D tree in C++. In this assignment, K=4. The K-D has a parent node, and a left and right node, which in turn can act as a parent node and have its own left and
right nodes, and so on.
Each internal node consists of it's dimension value that it discriminates by, the discriminate value, and it's left and right children.
Leaf nodes contain a bucket with no more than be elements. In this assignment, b=10. all the data is stored in the leaves.
Even though all nodes have dimension, discriminate, and bucket member variables, only some nodes have values for each of those, as described above.

This program taks in two parameters. The first is the determine have many points the tree should have, and the second is to determine how many probe points are going to be asked.
The program reads from input to fill in the values for the points. This program uses the randGen perl script to obtain the data.
These points are placed into a vector of vector of ints.
The K-D tree is then created. At each node, the best dimension to discriminate on is determined by looking at the dimension with the longest range.
Lomuto's partioning and QuickSelect are used to find the best value to discriminate on.
The data is then separated into two subarrays, and this process is started all over again using recursion.

Once the tree is created, probe points are searched for in the tree. The bucket that the point should fit into is found and printed out.



