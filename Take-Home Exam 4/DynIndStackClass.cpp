/******************************************************************************
Title: A C++ class for a Dynamic stack of matrix coordinates
Date: 06/04/2021
Any known bugs: none
References: DynIntStack.h
******************************************************************************/

/* Begin: code taken from DynIntStack.cpp and Updated */

#include <iostream>
#include "DynIndStackClass.h"
using namespace std;

//************************************************
// Constructor to generate an empty stack.       *
//************************************************
DynIndStack::DynIndStack()
{
	top = NULL; 
}

//******************************************
//Destructor function to deallocate memory *
//******************************************

DynIndStack::~DynIndStack()
{
	StackNode *temp;

	while (!isEmpty())
	{
		temp = top->next;
		delete top;
		top = temp;
	}

}
//************************************************
// Member function push pushes the argument onto *
// the stack.                                    *
//************************************************
void DynIndStack::push(int row, int col)
{
	StackNode *newNode;

	// Allocate a new node & store row and column values
	newNode = new StackNode;
	newNode->row = row;
	newNode->col = col;

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}
}

//****************************************************
// Member function pop pops the node at the top     *
// of the stack off, and copies it's row and column values into the variables*
// passed as an argument.                            *
//****************************************************
void DynIndStack::pop(int &row, int &col)
{
	StackNode *temp;

	if (isEmpty())
	{
		cout << "The stack is empty.\n";
	}
	else	// pop value off top of stack
	{
		row = top->row;
		col = top->col;
		temp = top->next;
		delete top;
		top = temp;
	}
}

//****************************************************
// Member funciton isEmpty returns true if the stack *
// is empty, or false otherwise.                     *
//****************************************************
bool DynIndStack::isEmpty(void)
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}

/* End: code taken from DynIntStack.cpp and updated */