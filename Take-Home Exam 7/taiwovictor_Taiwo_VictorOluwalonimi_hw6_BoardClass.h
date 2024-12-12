/****************************************************************************************
Title: A C++ Class for creating and using a Matching card board game
Author: Victor Oluwalonimi Taiwo
Student ID: 28579
Date: 09/05/2021
Note: Program closes if user attempts to open a card not within range, hence validity 
checks should be made in main before passing to board class
****************************************************************************************/



#ifndef _BOARD_H
#define _BOARD_H
#include <fstream>
#include <string>

using namespace std;

template<class itemType>
struct MatrixNode
{
	itemType info;
	bool isClosed;
};

template<class itemType>
class Board
{
	private:
		MatrixNode<itemType>** matrix;
		int rows;
		int cols;
	public:
		Board (); //default constructor
		Board (int rows, int cols);
		MatrixNode<itemType>** cloneMatrix () const;
		Board (const Board &); //deep copy constructor
		~Board (); //destructor
		void readBoardFromFile(ifstream & input); //extract board matrix content from a file
		void displayBoard() const; //display cards in Board
		void closeCard(int row, int col); //closes card with given index in Board
		itemType openCard(int row, int col); //opens card with given index in Board
		int getRow() const; //returns number of rows in Board
		int getColumn() const; //returns number of columns in Board
		bool isValid(int row, int col) const; //Checks to see if a passed index is valid for board
};

#include "taiwovictor_Taiwo_VictorOluwalonimi_hw6_BoardClass.cpp"

#endif