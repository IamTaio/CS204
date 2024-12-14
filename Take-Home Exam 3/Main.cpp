/******************************************************************************
Title: Displaying All Ordered Subsequences with a Hybrid Linked List Structure for a Given Line of Input
Date: 29/3/2021
Any known bugs: none
References: 
******************************************************************************/


#include <iostream>
#include "taiwovictor_Taiwo_VictorOluwalonimi_hw3_SubSeqsListClass.h"
#include <sstream>
using namespace std;

int main()
{
	string numbers;
	int entry;
	SubSeqsList list;
	cout << "Please enter the numbers in a line: ";
	getline(cin, numbers); //reads the whole line of input
	istringstream input(numbers); //read the integers individually
	cout << endl;
	while (input >> entry)
	{
		if (entry >= 0)//checks if entry is a non negative entry
		{
			list.AddSubSeq(entry);
		}
		else 
		{
			entry = entry * -1; //find absolute value of entry
			list.DeleteSubSeqHead(entry);
		}
	}
	cout << endl;
	cout << "FINAL CONTENT" << endl;
	list.DisplayList();
	list.Clear();
	
	return 0;
}