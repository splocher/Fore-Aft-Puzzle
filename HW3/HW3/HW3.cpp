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
			cout << "Thank You, and have a wonderful day!!!1!!1!!11!ONE!" << endl << endl;
		}
		return 0;
	}
	if (choice == 1) {
		//DFS
	}
	if (choice == 2) {
		//BFS
	}
	if (choice == 3) {
		//A*
	}
	return 0;
}

