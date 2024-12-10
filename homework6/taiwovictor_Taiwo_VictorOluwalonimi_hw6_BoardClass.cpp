#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "taiwovictor_Taiwo_VictorOluwalonimi_hw6_BoardClass.h"

using namespace std;

template<class itemType>
Board<itemType>::Board(int row = 0, int col = 0) 
	//constructor, initializes row and colmn to 0 and leaves an empty 2D array
{
	matrix = NULL;
	rows = row;
	cols = col;
}

template<class itemType>
Board<itemType>::~Board()
	//destructor
{
	if (matrix != NULL)
	{
		for (int i = 0; i < rows; i++)
		{
			delete [] matrix[i];
		}
		delete [] matrix;
	}
}

template<class itemType>
MatrixNode<itemType>** Board<itemType>::cloneMatrix () const
	//creates a clone of Board
{
	if (matrix == NULL)
	{
		return NULL;
	}
	
	MatrixNode<itemType>** clone;
	clone = new MatrixNode<itemType>*[rows];
	for (int i = 0; i<rows; i++) 
	{
		clone[i] = new MatrixNode<itemType>[cols]; 
	}
	for (int i = 0; i <  rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			clone[i][j] = matrix[i][j];
		}
	}
	return clone;
}

template<class itemType>
Board<itemType>::Board (const Board<itemType> & copy)
//deep copy constructor
{
	matrix = copy.cloneMatrix();
	rows = copy.rows;
	cols = copy.cols;
}

template<class itemType>
void Board<itemType>::readBoardFromFile(ifstream & input)
//Reads a 2D array from a file
//Assignes values to the respective indices
{
	matrix = new MatrixNode<itemType>*[rows];
	for (int i = 0; i<rows; i++) 
	{
		matrix[i] = new MatrixNode<itemType>[cols]; 
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j=0; j < cols; j++)
		{
			matrix[i][j].isClosed = true;
		}
	}
	string line;
	itemType value;
	for (int i = 0; i < rows; i++)
	{
		getline(input,line);
		stringstream bits(line);
		for (int j=0; j < cols; j++)
		{
			bits >> value;
			matrix[i][j].info = value;
		}
	}
}

template<class itemType>
void Board<itemType>::closeCard(int row, int col)
{
	if (rows < row || cols < col)
	{
		cout << "Card is out of range";
	}
	if (!matrix[row][col].isClosed)
	{
		matrix[row][col].isClosed = true;
	}
}

template<class itemType>
itemType Board<itemType>::openCard(int row, int col)
//Opens card of given index
//returns value stored in that index
//exits program if index is out of range, therefore use of this class requires validity checks before passing
{
	if (isValid(row,col) && matrix[row][col].isClosed)
	{ 
		matrix[row][col].isClosed = false;
		return matrix[row][col].info;
	}
	exit(1);
}

template<class itemType>
bool Board<itemType>::isValid(int row, int col) const
//Checks if a given index is valid for the board game 
//returns false for all values out of range
{
	if (row < 0 || row >= rows || col < 0 || col >= cols)
	{
		return false;
	}
	if (!matrix[row][col].isClosed)
	{
		return false;
	}
	return true;
}

template<class itemType>
void Board<itemType>::displayBoard() const
{
	if (matrix != NULL)
	{
		for (int i = 0; i < rows; i++)
		{
			string result = "";
			for (int j = 0; j < cols; j++)
			{
				if (matrix[i][j].isClosed)
				{
					result += "X ";
				}
				else
				{
					ostringstream output;
					output << matrix[i][j].info;
					result += output.str() + " ";
				}
			}
			cout << result.substr(0,result.length()-1) << endl;
		}
	}
}

template<class itemType>
int Board<itemType>::getRow() const
{
	return rows;
}

template<class itemType>
int Board<itemType>::getColumn() const
{
	return cols;
}