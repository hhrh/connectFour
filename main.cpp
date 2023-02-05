#include <iostream>
#include <cctype>
#include "LL.h"

//OUTPUT BOARD:
//returns current state of the board
//chips are represented with R or B, empty space are represented with a "-"
void outputBoard(LL<bool> board[]) {
	std::cout << std::endl;
	for (int j = 7; j >= 1; j--) {
		for(int i = 0; i <= 6; i++) {
			//if no node at position:
			if (board[i].size() < j) {
				std::cout << " - ";
			}
			//if j is at a node:
			//gets the node at j and prints it
			else {
				LL<bool>::Iterator it(board[i].begin());
				int counter = 1;
				while(it !=board[i].end()) {
					if (counter == j)
						break;
					it++;
					counter++;
				}
				std::cout << " " << (*it==0?"R":"B") << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << "\n A  B  C  D  E  F  G\n\n";
}

//==========WIN CONDITION FUNCTIONS==========//
//VERTICAL CHECK:
//returns true if there are 4 vertical chips of the same kind in a row
bool verticalCheck(LL<bool> board[]) {
	for (int i = 0; i <= 6; i++ ) {
		//if LL has less than 4 nodes, vertical win not possible
		if(board[i].size() < 4) {
			continue;
		}
		LL<bool>::Iterator it1(board[i].begin());
		LL<bool>::Iterator it2 = it1;
		it2++;
		int winCounter = 1;

		//increments thru single LL, counts chips if same
		for(int j = 1; j < board[i].size(); j++) {
			if (*it1 != *it2) {
				it1 = it2;
				it2 = it1;
				it2++;
				winCounter = 1;
			}
			else {
				it2++;
				winCounter++;
				//if 4 in a row, win
				if (winCounter >= 4) {
					return true;
				}
			}
		}
	}
	return false;
}

//DIAGONAL CHECK:
//returns true if there are 4 chips of the same kind in a row diagonally
//checks negative slant and positive slant.
bool diagonalCheck(LL<bool> board[]) {
	//positive slope win:
	for (int i = 0; i <= 3; i++) { //cols
		int winCounter = 1;

		//if column is empty, nothing to check, go next row
		if (board[i].size() == 0)
			continue;

		LL<bool>::Iterator it1(board[i].begin());

		for (int j = 1; j <= 4; j++) { //rows
			//if end of column is reached, break, go next row
			winCounter = 1;
			if(j > board[i].size())
				break;

			//win logic: check for positive diag slope at (i,j):
			//k represents the index's of the possible diag win columns
			int rowCnt = 1;
			int diagPosition = j+1;
			for (int k = i+1; k <= i+3; k++) {

				//if next col has no positive diagonal node, win not posibble, go next row
				if (board[k].size() < diagPosition)
					break;

				LL<bool>::Iterator it2(board[k].begin());
				//loop to get diagonally adjacent node;
				for(; it2 != board[k].end(); it2++) {

					//if reached diag pos, set new diag pos for next col.
					if(rowCnt == diagPosition) {
						diagPosition++;
						rowCnt = 1;
						break;
					}
					rowCnt++; //keeps track of it2's position in LL
				}

				//if nodes dont match, diag win not possible, go next row
				if (*it1 != *it2) {
					//winCounter = 1;
					break;
				}
				winCounter++; //if nodes match, add to counter
				if (winCounter >= 4) {
					return true;
				}
			}
			it1++; //position j
		}
	} 

	//negative slope win:
	for (int i = 0; i <= 3; i++) { //cols

		//if column size is less than 4, win not possible, go next row
		if (board[i].size() < 4)
			continue;

		//initialize base iterator to starting point(4th row)
		LL<bool>::Iterator it1(board[i].begin());
		int startCnt = 1;
		for (; it1 != board[i].end(); it1++) {
			if (startCnt == 4)
				break;
			startCnt++;
		}
		int winCounter = 1;

		for (int j = 4; j <= 7; j++) { //rows
			winCounter = 1;

			//if end of column is reached, break, go next row
			if(j > board[i].size()) {
				break;
			}

			//win logic: check for negative diag slope at (i,j):
			//k represents the index's of the possible diag win columns
			int rowCnt = 1;
			int diagPosition = j-1;
			for (int k = i+1; k <= i+3; k++) {

				//if next col has no negative diagonal node, win not possible, go next row
				if (board[k].size() < diagPosition)
					break;

				LL<bool>::Iterator it2(board[k].begin());
				//loop to get diagonally adjacent node;
				for(; it2 != board[k].end(); it2++) {

					//if reached diag pos, set new diag pos for next col.
					if(rowCnt == diagPosition) {
						diagPosition--;
						rowCnt = 1;
						break;
					}
					rowCnt++; //keeps track of it2's position in LL
				}

				//if nodes dont match, diag win not possible, go next row
				if (*it1 != *it2) {
					break;
				}
				winCounter++; //if nodes match, add to counter
				if (winCounter >= 4) {
					return true;
				}
			}
			it1++; //position j
		}
	} 

	return false; //no win found, return false
}

//HORIZONTAL CHECK:
//returns true if there are 4 chips of the same kind in a row horizontally
bool horizontalCheck(LL<bool> board[]) {

	for (int i = 0; i <= 3; i++) { //cols

		//if column is empty, nothing to check, go next row
		if (board[i].size() == 0)
			continue;

		//initialize base iterator
		LL<bool>::Iterator it1(board[i].begin());
		int winCounter = 1;

		for (int j = 1; j <= 7; j++) { //rows
			winCounter = 1;

			//if end of column is reached, break, go next row
			if(j > board[i].size()) {
				break;
			}

			//win logic: check for horizontal win at (i,j):
			//k represents the index's of the possible horizontal win columns
			int rowCnt = 1;
			int nextPosition = j;
			for (int k = i+1; k <= i+3; k++) {

				//if next col has no horizontally adjacent node, win not possible, go next row
				if (board[k].size() < nextPosition)
					break;

				LL<bool>::Iterator it2(board[k].begin());
				//loop to get horizontally adjacent node;
				for(; it2 != board[k].end(); it2++) {

					if(rowCnt == nextPosition) {
						rowCnt = 1;
						break;
					}
					rowCnt++; //keeps track of it2's position in LL
				}

				//determine match logic:
				//if nodes dont match, horizontal win not possible, go next row
				if (*it1 != *it2) {
					break;
				}
				winCounter++; //if nodes match, add to counter
				if (winCounter >= 4) {
					return true;
				}
			}
			it1++; //position j
		}
	} 
	return false;	//no win found, return false
}

int main()
{
	char ch;
	int col = -1;
	bool turn;
	int numOfMoves = 0;

	//initialize board, 7 linked lists
	LL<bool> board[7];
	outputBoard(board);

	while (numOfMoves < 49) {
		
	//prompt:
	do {
		std::cout << (turn == 0 ? "Red " : "Blue ") << "Player Select a row: ";

		//convert letter to column number:
		std::cin >> ch;
		col = tolower(ch) - 'a';

		//error checking:
		if(col < 0 || col > 6) {
			std::cout << "Invalid Column\n";
			continue;
		}
		if(board[col].size() == 7) {
			std::cout << "Invalid Move\n";
			col = -1;
		}
	}
	while (col < 0 || col > 6);
	
	//insert chip into selected column:
	board[col].tailInsert(turn);
	outputBoard(board);

	//after every move, check all win conditions:
	if(verticalCheck(board) || horizontalCheck(board) || diagonalCheck(board)) {
		std::cout << (turn == 0 ? "Red " : "Blue ") << "Wins!\n";
		return 0;
	}

	turn = !turn;
	numOfMoves++;
	}
	
	//last check if not tie
	if(verticalCheck(board) || horizontalCheck(board) || diagonalCheck(board)) {
		std::cout << (turn == 0 ? "Red " : "Blue ") << "Wins!\n";
		return 0;
	}

	std::cout << "\nTie." << std::endl;
	return 0;
}
