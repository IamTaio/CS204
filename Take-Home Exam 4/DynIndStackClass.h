/******************************************************************************
Title: A C++ class for a Dynamic stack of matrix coordinates
Author: Victor Oluwalonimi Taiwo
Student ID: 28579
Date: 06/04/2021
Any known bugs: none
References: DynIntStack.h
******************************************************************************/

/* Begin: code taken from DynIntStack.cpp and Updated */


#ifndef DynIndStackClass_H
#define DynIndStackClass_H

struct StackNode //struct for the stack nodes 
{
	int row;
	int col;
	StackNode *next;
};

class DynIndStack
{
private:
	StackNode *top;

public:
	DynIndStack();
	~DynIndStack();
	void push(int, int);
	void pop(int &, int &);
	bool isEmpty();
};

#endif

/* End: code taken from DynIntStack.cpp and updated*/