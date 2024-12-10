/******************************************************************************
Title: Displaying Sorted Subsequences with Linked Lists
Author: Victor Oluwalonimi Taiwo
Student ID: 28579
Date: 16/3/2021
Any known bugs: It works fine for txt files but crashes on empty input files
References: ptrfunc.cpp
******************************************************************************/

#include <iostream>
#include <string>
#include "strutils.h"
#include <sstream>
using namespace std;

struct node /* struct for making linked list */
{
	int value;
	node* next;
};

/* Begin: code taken from ptrfunc.cpp and updated with different sorting orders*/
// Function to insert a node in ascending order
node * AddInAscendingOrder(node * head, int newkey)
// pre: list is sorted
// post: add newkey to list, keep list sorted, return head of new list
{
   node *  ptr = head;   // loop variable

   // if new node should be first, handle this case and return  
   // in this case, we return address of new node since it is new head  
   if (head == NULL || newkey < head->value)        
    {   
		node * temp = new node;  //node to be inserted 
		temp->value = newkey;
		temp->next = head; //connect the rest
		return temp;
    }

    // check node one ahead so we don't pass!
   while (ptr->next != NULL && ptr->next->value < newkey)
    {    
		ptr = ptr->next;
    } // postcondition: new node to be inserted just after the node ptr points

    //now insert new node with newkey after where ptr points to
	node * temp = new node;  //node to be inserted 
	temp->value = newkey;
	temp->next = ptr->next; //connect the rest
	ptr->next = temp;

	return head;
}
// Function to insert node in descending order
node * AddInDescendingOrder(node * head, int newkey)
// pre: list is sorted
// post: add newkey to list, keep list sorted, return head of new list
{
   node *  ptr = head;   // loop variable

   // if new node should be first, handle this case and return  
   // in this case, we return address of new node since it is new head  
   if (head == NULL || newkey > head-> value)        
    {   
		node * temp = new node;  //node to be inserted 
		temp->value = newkey;
		temp->next = head; //connect the rest
		return temp;
    }

    // check node one ahead so we don't pass!
   while (ptr->next != NULL && ptr->next-> value > newkey)
    {    
		ptr = ptr->next;
    } // postcondition: new node to be inserted just after the node ptr points

    //now insert new node with newkey after where ptr points to
	node * temp = new node;  //node to be inserted 
	temp->value = newkey;
	temp->next = ptr->next; //connect the rest
	ptr->next = temp;

	return head;
}

/* End: code taken from ptrfunc.cpp and updated with different sorting orders */

//Deleting values greater than/lesser than the node for the ascending/descending order lists
string DeleteOrder (node * &head, int insertedvalue)
//pre: list is sorted
//post: every node after specified node is deleted while maintaining sorting order
//returns all values that were deleted as a string
{
	node * ptr = head; //loop variable
	node * ptr2 = NULL;
	while (ptr -> next != NULL && ptr->value != insertedvalue) 
	{
		ptr = ptr -> next;
	} //postcondition: ptr is now at specified node

	ptr2 = ptr -> next; //ptr2 now points at the next node
	string DeletedValues = "";
	/* Begin: code taken from ptrfunc.cpp and updated */
	node * temp;
	while (ptr2 != NULL) 
	{
		if (DeletedValues == "") {
			DeletedValues += itoa(ptr2->value);
		}
		else {
			DeletedValues += " " + itoa(ptr2->value); //stores values of deleted nodes
		}
		temp = ptr2 -> next;
		delete ptr2;
		ptr2 = temp;
	}//all nodes after specified are deleted
	ptr -> next = ptr2; //makes the last node NULL
	if (DeletedValues.size() < 1) //if there are no nodes deleted returns none
	{
		return "None";
	}
	return DeletedValues;
}

string DisplayList(node * head)
//Displays all values in a linked list as a string 
{
	node * ptr = head; //Loop Variable
	string list = "";
	if (ptr != NULL) {
		list += itoa(ptr->value);
		ptr = ptr->next;
	}
	while ( ptr != NULL) 
	{
		list += " " + itoa(ptr->value);
		ptr = ptr -> next;
	}
	return list;
}

bool CheckInList(node * head, int key)
//Checks if a specified value is already present in given list
{
	node * ptr = head; //loop variable
	while (ptr != NULL) //goes through all nodes in the list
	{
		if (ptr-> value == key)
		{
			return true;
		}
		ptr = ptr -> next;
	}
	return false;
}

int main()
{
	string order, numbers, deletednodes;
	int entry, count = 0;
	node * head = NULL;
	cout << "Please enter the order mode (A/D): ";
	cin >> order;
	while (order != "A" && order != "D") //check to see if input is entered correctly
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout << "Please enter the order mode again (A/D): ";
		cin >> order;
	}
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	cout << "Please enter the numbers in a line: ";
	getline(cin, numbers); //reads the whole line of input
	istringstream input(numbers); //read the integers individually
	while (input >> entry)
	{
		count++; //checks to see if any integer values are read
		cout << endl;
		cout << "Next number: " << entry << endl;
		if (CheckInList(head, entry)) //validating that new value is not already present 
		{
			cout << entry << " is already in the list!" << endl;
		}
		else
		{
			if (order == "A") 
			{
				head = AddInAscendingOrder(head, entry);
			}
			else if (order == "D")
			{
				head = AddInDescendingOrder(head, entry);
			}
			cout << "Deleted nodes: " << DeleteOrder(head, entry)<< endl; 
			cout << "Appended: " << entry << endl;
		}
		cout << "List content: " << DisplayList(head) << endl;
	}
	if (count == 0) //No integers were read
	{
		cout << endl;
		cout << "The list is empty at the end of the program and nothing is deleted" << endl;
	}
	else 
	{
		cout << endl;
		cout << "All the nodes are deleted at the end of the program: " << DisplayList(head) << endl;
		deletednodes = DeleteOrder(head, head->value); //Deletes all nodes after the head node 
		delete head; //Deletes the head
	}
	return 0;
}



