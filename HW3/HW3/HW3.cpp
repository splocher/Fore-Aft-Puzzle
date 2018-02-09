/* Name: Shane Plocher
* Date: 02/15/2018
* Class: CS438 – Introduction to Artificial Intelligence
* Assignment: HW3 – Fore & Aft
* Comments:
* Search Methods:
* Run Time:
*/

#include "stdafx.h"
#include <string>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
//A* psuedo
/*
1	Create a node containing the goal state node_goal
2	Create a node containing the start state node_start
3	Put node_start on the open list
4	while the OPEN list is not empty
5	{
6	Get the node off the open list with the lowest f and call it node_current
7	if node_current is the same state as node_goal we have found the solution; break from the while loop
8	    Generate each state node_successor that can come after node_current
9	    for each node_successor of node_current
10	    {
11	        Set the cost of node_successor to be the cost of node_current plus the cost to get to node_successor from node_current
12	        find node_successor on the OPEN list
13	        if node_successor is on the OPEN list but the existing one is as good or better then discard this successor and continue
14	        if node_successor is on the CLOSED list but the existing one is as good or better then discard this successor and continue
15	        Remove occurences of node_successor from OPEN and CLOSED
16	        Set the parent of node_successor to node_current
17	        Set h to be the estimated distance to node_goal (Using the heuristic function)
18	         Add node_successor to the OPEN list
19	    }
20	    Add node_current to the CLOSED list
21	}
*/


int main()
{
	int choice;

	//ask the user for input
	cout << "	Select a search method:" << endl;
	cout << "	1. Depth First Search" << endl;
	cout << "	2. Breadth First Search" << endl;
	cout << "	3. Best First Search" << endl;
	cout << "	4. Exit" << endl;
	cin >> choice;
	cout << endl;

	if (choice == 4) {
		//print a comment and quit, I made a random comment appear when you quit just for fun
		int randomComment;
		srand(time(NULL));
		randomComment = rand() % 3 + 1;
		if (randomComment == 1) {
			cout << "Have a #blessed day!" << endl << endl;
		}
		if (randomComment == 2) {
			cout << "Why are you leaving me? Whatever, Just go..." << endl << endl;
		}
		else if (randomComment == 3) {
			cout << "Thank You, and have a wonderful day!!!" << endl << endl;
		}
		return 0;
	}
	if (choice == 1) {
		//DFS
		cout << "Enter Puzzle size for DFS (5 or 7): " << endl;
	}
	if (choice == 2) {
		//BFS
		cout << "Enter Puzzle size for BFS (5 only): " << endl;
	}   
	if (choice == 3) {
		//A*
		cout << "Enter Puzzle size for A* (5 - 13): " << endl;
	}
	return 0;
}

