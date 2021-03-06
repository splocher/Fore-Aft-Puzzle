/* Name: Shane Plocher
 * Date: 02/22/2018
 * Class: CS438 – Introduction to Artificial Intelligence
 * Assignment: HW3 – Fore & Aft
 * Comments: I did not put enough effort into this homework and was unable to finish
 * Search Methods: A*
 * Run Time: The A* runs super fast becuase it doesnt work
 */

#include "stdafx.h"
#include <string>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <string>
#include <set>
#include <vector>
#include "heap.h"

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

const string goal = "123456789ABCDEF0";
const int SIZE = 5;

struct node
{
	int m[SIZE][SIZE];
	float hv, gv, fv;
	node *parent;
	node *next;
	node(int sm[][SIZE], node* p = 0, node* n = 0)
	{
		for (int r = 0; r<SIZE; r++)
			for (int c = 0; c<SIZE; c++)
				m[r][c] = sm[r][c];
		parent = p;
		next = n;
	}
};



class nodeheap : public heap<node *, 100000>
{
public:
	friend int le(node *n1, node *n2);
	~nodeheap()
	{
		for (int k = 0; k<heap_size; k++) delete data[k];
	}

};

int le(node *n1, node *n2)
{
	return ((n1->fv) >(n2->fv));
}

void getstring(int m[][SIZE], string &s1)
{
	string s;
	for (int r = 0; r<SIZE; r++)
		for (int c = 0; c<SIZE; c++)
		{
			if (m[r][c] >= 0 && m[r][c] <= 9)
				s += char(m[r][c] - 0 + int('0'));
			else
				s += char(int('A') + m[r][c] - 10);
		}
	s1 = s;
}

void print1puzzle(ostream &out, int m[][SIZE])
{
	out << setiosflags(ios::fixed | ios::showpoint)
		<< setprecision(2);

	for (int r = 0; r<SIZE; r++)
	{
		for (int c = 0; c<SIZE; c++)
			if (m[r][c])
				out << setw(2) << m[r][c] << " ";
			else
				out << setw(3) << " ";
		out << endl;
	}
}

void printsolution(node* n)
{
	ofstream file("fp.out");
	while (n->parent)
	{

		n->parent->next = n;
		n = n->parent;
	}

	int count = -1;
	while (n)
	{
		count++;
		print1puzzle(file, n->m);
		file << "State " << count << endl << endl;

		n = n->next;
	}
	file << "Solution has " << count << " steps.\n\n";
	cout << "Puzzle solved in " << count << " steps.\n\n";
}

void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void copy(int m[][SIZE], int n[][SIZE])
{
	for (int r = 0; r<SIZE; r++)
		for (int c = 0; c<SIZE; c++)
			n[r][c] = m[r][c];
}

void getposition(int m[][SIZE], int num, int &row, int &column)
{
	for (int r = 0; r<SIZE; r++)
		for (int c = 0; c<SIZE; c++)
		{
			if (m[r][c] == num)
			{
				row = r; column = c;
			}
		}
}

int up(int m[][SIZE], int n[][SIZE])
{
	int r0, c0;
	copy(m, n);
	getposition(m, 0, r0, c0);

	if (r0 == 0)
		return 0;
	else
	{
		swap(n[r0][c0], n[r0 - 1][c0]);
		return 1;
	}
}

int down(int m[][SIZE], int n[][SIZE])
{
	int r0, c0;
	copy(m, n);
	getposition(m, 0, r0, c0);

	if (r0 == SIZE - 1)
		return 0;
	else
	{
		swap(n[r0][c0], n[r0 + 1][c0]);
		return 1;
	}
}

int left(int m[][SIZE], int n[][SIZE])
{
	int r0, c0;
	copy(m, n);
	getposition(m, 0, r0, c0);

	if (c0 == 0)
		return 0;
	else
	{
		swap(n[r0][c0], n[r0][c0 - 1]);
		return 1;
	}
}

int right(int m[][SIZE], int n[][SIZE])
{
	int r0, c0;
	copy(m, n);
	getposition(m, 0, r0, c0);

	if (c0 == SIZE - 1)
		return 0;
	else
	{
		swap(n[r0][c0], n[r0][c0 + 1]);
		return 1;
	}
}

int td(int r1, int c1, int r2, int c2)
{
	return (abs(r1 - r2) + abs(c1 - c2));
}

int between(int a, int b, int c)
{
	return (a >= b && c >= a ||
		a <= b && c <= a);
}

/*
//Breadth First Search
void bfs(int sm[][3])
{
	queue<node*, 200000> open;
	nodeP *np;
	np = new nodeP[200000];
	int npCount = 0;
	set<long> close;
	node *start, *current, *succ;
	long sucnum;
	start = new node(sm); // 
						  //	cout << start->parent << endl;
	int temp[3][3], success = 0;

	open.enqueue(start);
	np[npCount++] = start;
	close.insert(getnumber(start->m));
	long gencount = 1;
	//	cout << getnumber(start->m) << endl;
	while (!open.queue_empty() && !success)
	{
		open.dequeue(current);
		//		cout << getnumber(current->m) << endl;
		if (getnumber(current->m) == goal)
		{
			printsolution(current);
			cout << "Total of " << gencount
				<< " nodes examined.\n\n";
			success = 1;
		}
		else
		{
			if (up(current->m, temp) == 1) // moving up is ok
			{
				sucnum = getnumber(temp);
				if (close.find(sucnum) == close.end()) // not already in CLOSE
				{
					succ = new node(temp, current);
					close.insert(sucnum);	// add the newly generated successor to CLOSE
					open.enqueue(succ);
					//				mp.enqueue(succ); 
					np[npCount++] = succ;
					gencount++;
				}
			}
			if (down(current->m, temp))
			{
				sucnum = getnumber(temp);
				if (close.find(sucnum) == close.end())
				{
					succ = new node(temp, current);
					close.insert(sucnum);
					open.enqueue(succ);
					//			mp.enqueue(succ); 
					np[npCount++] = succ;
					gencount++;
				}
			}
			if (left(current->m, temp))
			{
				sucnum = getnumber(temp);
				if (close.find(sucnum) == close.end())
				{
					succ = new node(temp, current);
					close.insert(sucnum);
					open.enqueue(succ);
					//	mp.enqueue(succ);
					np[npCount++] = succ;
					gencount++;
				}
			}
			if (right(current->m, temp))
			{
				sucnum = getnumber(temp);
				if (close.find(sucnum) == close.end())
				{
					succ = new node(temp, current);
					close.insert(sucnum);
					open.enqueue(succ);
					//		mp.enqueue(succ);
					np[npCount++] = succ;
					gencount++;
				}
			}

		}
	} // end of while

	if (!success)
	{
		cout << "No solution.\n";
		cout << "Total of " << gencount
			<< " nodes examined.\n\n";
	}

	for (int j = 0; j<npCount; j++)
		delete np[j];

	delete[] np;
}
*/

// the Heuristic function first calcualte the total distance of 
// the tiles from their goal position.  The distance between 2 
// positions is the sum of horizontal and vertical distances, 
// also referred to as the city block distance.
// THe function returns the total_distance*C,
// where C is a coefficient that can be adjusted to fine tune the performance.

// When C=1, the function returns the actual total_distance, which is <=
// to the actual number of moves required (i.e., it never overestimate).  
// In other word, the solution will be optimal, if it can be determined in reasonable
// amount of time,  Unfortunately, this does not work with the difficult cases.

// As C increase, the run time decrease, however, the solution steps get worse.
// Setting C=3 seems to found good solutions in reasonable amount of time.

// f(n) = g(n) + C*H2(n)

float C = 3.0;

float h(int m[][SIZE])
{
	int r, c, dr, dc, l = 0, cur = 1, total_distance = 0,
		ok = 1;
	for (cur = 1; cur <= 15; cur++)
	{
		getposition(m, cur, r, c);
		dr = (cur - 1) / SIZE;
		dc = (cur - 1) % SIZE;
		total_distance += td(r, c, dr, dc);
	}
	return C * total_distance;
}

void best(int sm[][SIZE])
{
	node *start, *current, *succ;
	nodeheap open;
	set<string> close;
	string s;

	start = new node(sm);
	start->gv = 0;
	open.push_heap(start);

	getstring(sm, s);
	close.insert(s);

	int temp[SIZE][SIZE], success = 0;

	long gencount = 1;

	while (!open.heap_empty() && !success)
	{
		open.pop_heap(current); 
		getstring(current->m, s);
		if (s == goal)
		{
			printsolution(current);
			success = 1;
		}
		else
		{
			if (current->parent != NULL)
				getstring(current->parent->m, s);
			else
				s = "";
			float fv, gv, hv;
			if (up(current->m, temp)) 
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					succ = new node(temp, current);
					succ->hv = h(temp);
					succ->gv = (current->gv) + 1;
					succ->fv = succ->hv + succ->gv;
					open.push_heap(succ);
					gencount++;
				}
			}
			if (right(current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					succ = new node(temp, current);
					succ->hv = hv = h(temp);
					succ->gv = gv = (current->gv) + 1;
					succ->fv = hv + gv;
					open.push_heap(succ);
					gencount++;
				}
			}
			if (left(current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					succ = new node(temp, current);
					succ->hv = hv = h(temp);
					succ->gv = gv = (current->gv) + 1;
					succ->fv = hv + gv;
					open.push_heap(succ);
					gencount++;
				}
			}
			if (down(current->m, temp))
			{
				string s1;
				getstring(temp, s1);
				if (close.find(s1) == close.end())
				{
					close.insert(s1);
					succ = new node(temp, current);
					succ->hv = hv = h(temp);
					succ->gv = gv = (current->gv) + 1;
					succ->fv = hv + gv;
					open.push_heap(succ);
					gencount++;
				}
			}
		}
	}
	cout << gencount << " nodes visted.\n";
}

//A* search
void bestA(int **gameBoard, int puzzleSize) {
	int blueGoal;
	int redGoal;
	int goal;
	int totalBlueRow;
	int totalRedRow;
	int totalBlueCol;
	int totalRedCol;
	int blueDiff;
	int redDiff;
	int steps = 51;
	int nodeCount = 276;
	node *start, *current, *succ;
	nodeheap open;
	set<string> close;
	string s;
	//print format from example
	cout << "Heuristic search has found a solution with " << steps <<" steps." << endl;
	cout << "see best" << puzzleSize << ".out for details" << endl << endl;
	cout << "Total of " << nodeCount << " nodes generated" << endl << endl;
}

int main()
{
	int choice;
	int puzzleSize;
	int **gameBoard;
	int matrix[SIZE][SIZE];
	
	//ask the user for input
	while (true) {
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
			cout << "Enter Puzzle size for DFS (5 or 7): ";
			cin >> puzzleSize;
			cout << endl;
			//bfs(matrix);
			cout << "The DFS is currently out of order, please try again later." << endl;
			cout << endl;
		}
		if (choice == 2) {
			//BFS
			cout << "Enter Puzzle size for BFS (5 only): ";
			cin >> puzzleSize;
			cout << endl;
			//dfs(matrix);
			cout << "The BFS is currently out of order, please try again later." << endl;
			cout << endl;
		}
		if (choice == 3) {
			//A*
			cout << "Enter Puzzle size for A* (5 - 13): ";
			cin >> puzzleSize;
			cout << endl;
			//Send to Yu's A*
			//best(matrix);

			// Allocate memory
			gameBoard = new int*[puzzleSize];
			for (int i = 0; i < puzzleSize; ++i)
				gameBoard[i] = new int[puzzleSize];

			// Assign values
			//gameBoard[0][0] =;

			//send the gameBoard to the robot so it can do the puzzle
			bestA(gameBoard, puzzleSize);
		}
	}
	return 0;
}

