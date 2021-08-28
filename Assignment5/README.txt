Assignment 5: Families
Author: Bobby Bose
Makefile code provided by Dr. Finkel. Edited by Bobby Bose to properly zip README.txt.
NOTE: Dr. Finkel's notes were used as reference in the writing of Breadth-first search.

Instructions on compiling: Type in "make run" into the command line to compile and run the program.
Output is pushed into a file named tmpRun.out

Purpose of this program is to simulate a genealogical database using a graph. The graph consists of two types of vertices: person and family.
There are at most 99 people and 99 families.
A person vertex is connected to two family vertices through "parents" and "marriage" edges.
A family vertex is connected to person vertices through "husband," "wife," and "children" edges. A family can have at most 10 children.

The program takes in one parameter: the data file to be read.
The program reads in line by line from the data file, and based on the first word on the line, performs one of four commands.

The Person command introduces a new person vertex and potentially connects them to parents and marriage family vertices. The number 0 is used to mean "unknown."
A line is printed with the details of the new person.

The Family command introduces a new family vertex and potentially connects them to husband, wife, and children person vertices. The number 0 is used in the same way here.
A line is printed with the details of the new family.

The Verify command checks the data for consistency. Specifically, it checks to make sure that whenever a vertex points to another vertex, that vertex also points back.
A line is printed for each inconsistency.

The Relate command finds the shortest path from one person vertex to another person vertex. The program uses a Breadth-first search technique to do this.
A Queue has been implemented for the BFS technique, using a linkedList class.
A line is printed displaying the shortest path between the two people.

