/****************************************************************************************
Title: A C++ Program for finding paths in matrix using only downward and right movement
Date: 06/04/2021
Any known bugs: none
References: DynIntStack.h
****************************************************************************************/


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "DynIndStackClass.h"
using namespace std;

struct cellStruct //struct to keep matrix values
{
	char value;
	bool IsTrap;
};

void print_table(cellStruct** values,  int num_rows, int num_cols);

/* Begin: code taken from strutils.cpp*/
string itoa(int n)
// postcondition: return string equivalent of int n
{
    ostringstream output;
    output << n;   
    return output.str();
}
/* End: code taken from strutils.cpp*/

void MatrixEditor(cellStruct** & matrix, string filename,const int rows,const int cols) 
	//Creates a matrix with the specified number of rows and columns
	//Fills the matrix with the values gotten from the file
{
	int i,j;
	for (i = 0; i < rows; i++)
	{
		for (j=0; j < cols; j++)
		{
			matrix[i][j].value = '0';
			matrix[i][j].IsTrap = true;
		}
	}

	
	//after loop all matrix cells are initialized to zero with a bool value of true
	ifstream input;
	string bits;
	input.open(filename.c_str());
	for (i = 0; i < rows; i++)
	{
		input >> bits; //reads a line of input for each row
		for (j=0; j< cols; j++)
		{
			matrix[i][j].value = bits[j]; //matches the column to the respective index of the line
			matrix[i][j].IsTrap = false; //initialize to false
		}
	}
	return;
}

bool CheckRight(cellStruct** matrix, int row, int col, int max_cols, char value)
//Checks if the cell to the immediate right is a potential path
{
	col++;
	if (col >= max_cols) //checks if we are at the edge of the matrix
	{
		return false;
	}
	else if (matrix[row][col].IsTrap)//checks the boolean value of the cell
	{
		return false;
	}
	else if (matrix[row][col].value != value)//checks if the value matches
	{
		return false;
	}
	return true;
}

bool CheckDown(cellStruct** matrix, int row, int col, int max_rows, char value)
//Checks if the downward cell is a potential path
{
	row++;
	if (row >= max_rows)
	{
		return false;
	}
	else if (matrix[row][col].IsTrap)
	{
		return false;
	}
	else if (matrix[row][col].value != value)
	{
		return false;
	}
	return true;
}
	
bool FindString (cellStruct ** matrix,const int num_rows,const int num_cols, string bits, DynIndStack &stack)
{
	//finds a path in the matrix that matches with our bits string
	int len = bits.length();
	for (int i = 0; i < num_rows; i++)
	{
		for (int j = 0; j < num_cols; j++)
		{
			matrix[i][j].IsTrap = false;
		}
	}
	//after loop all matrix cells have boolean values reset to false
	int row, col, count;
	row = col = count = 0;
	if (matrix[row][col].value != bits.at(count)) //Checks if the first bit matches with the origin value
	{
		return false;
	}
	stack.push(row,col);
	count++; //loop variable also keeps track of what string index we are at
	while (count < len)
	{
		if (count <= 0)
		{
			return false; //checks if (0,0) fails as a potential path
		}
		if(CheckRight(matrix,row,col,num_cols,bits[count]))
		{
			col++;
			stack.push(row,col);
			count++; //if right cell is a potential path, push and increment count
		}
		else if (CheckDown(matrix,row,col,num_rows,bits[count]))
		{
			row++;
			stack.push(row,col);
			count++;//if downward cell is a potential path, push and increment count
		}
		else
		{
			stack.pop(row,col); //pop if both directions fail as potential paths
			count--; //decrement count
			if (count <= 0)
			{
				return false; //prevents stack from popping (0,0)
			}
			matrix[row][col].IsTrap = true;
			stack.pop(row,col);
			stack.push(row,col); //pop and push to backtrack, i.e row and col now have same value as top stack node
		}
	}
	
	return true;
}



void print_stack(DynIndStack &stack)
{
	//prints all values in stack
	//postcondition: all stack nodes are deleted
	int x,y;
	string path;
	while(!stack.isEmpty())
	{
		stack.pop(x,y);
		path = "(" + itoa(x) + "," + itoa(y) + ")" + " " + path;
	}
	cout << path.substr(0,path.length()-1) << endl;
}


bool FileCheck(string filename, int rows, int cols)
	//Checks number of characters in file
	//Compares it to matrix specification
{
	ifstream input;
	string bits;
	int count = 0, size;
	input.open(filename.c_str());
	input >> bits;
	count += bits.length();
	while (!input.eof())
	{
		input >> bits;
		count += bits.length();
	}
	size = rows*cols;
	if (count != size)
	{
		return false;
	}
	return true;
}


int main(){
	int rows, cols;
	string bits;
	ifstream input;
	string filename;
	DynIndStack stack;
	cellStruct** Matrix;
	cout << "Please enter the number of rows: ";
	cin >> rows;
	cout << "Please enter the number of columns: ";
	cin >> cols;	
	cout << "Please enter the name of the input file that contains the matrix: ";
	cin >> filename;
	input.open(filename.c_str());
	while (input.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n'); //clear input buffer
		cout << "File cannot be opened." << endl;
		cout << "Please enter the name of the input file again: ";
		cin >> filename;
		input.open(filename.c_str());
	}
	//after while filename is confirmed to be the name of an actual file
	input.close(); 
	while (!FileCheck(filename,rows,cols)) 
		//confirms that file contains a matrix
		//of size matching specified rows and columns
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n'); //clear input buffer
		cout << "Matrix of wrong size found in file." << endl;
		cout << "Please enter the name of the input file again: ";
		cin >> filename;
		input.open(filename.c_str());
	}
	input.close();
	int i;
	/* Begin: code taken from matrixnoclass.cpp */
	Matrix = new cellStruct*[rows]; 
	for (i = 0; i<rows; i++) 
	{
		Matrix[i] = new cellStruct[cols]; 
	}
	/* End: code taken from matrixnoclass.cpp */
	MatrixEditor(Matrix,filename,rows, cols);
	cout << endl;
	cout << "Please enter a string of bits to search (CTRL+Z to quit): ";
	cin >> bits;
	while(!cin.eof()) //initiates loop until user enter CTRL+Z
	{
		if (FindString(Matrix, rows, cols, bits, stack))
		{
			cout << "The bit string " << bits <<  " is found following these cells:" << endl;
			print_stack(stack);
		}
		else 
		{
			cout << "The bit string " << bits <<  " could not be found." << endl;
		}
		cout << "---------------------------------------------------------" << endl;
		cout << "Please enter a string of bits to search (CTRL+Z to quit): ";
		cin >> bits;
	}
	cout << "Program ended successfully!"<< endl;
	cout << endl;
	/* Begin: code taken from matrixnoclass.cpp */

	for (int i = 0; i< rows; i++) // Returning memory to free heap for reuse
	{							 
		delete [] Matrix[i]; 
	}
	delete [] Matrix;
	/* End: code taken from matrixnoclass.cpp */
	return 0;
}
