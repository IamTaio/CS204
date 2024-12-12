#include <iostream>
#include "SubSeqsListClass.h"
using namespace std;

SubSeqsList::SubSeqsList() //Creates a new linked list and initializes the head value as NULL
{
	hHead = NULL;
};

bool SubSeqsList::IsEmpty() //Checks if the linked list is empty
{
	if (hHead == NULL)
	{
		return true;
	};
	return false;
};

/* Begin: code taken from ptrfunc.cpp and updated*/
void SubSeqsList::Clear() //Delete all nodes in the linked list
{
	SubSeqHeadNode * ptr = hHead;//loop variable
	while (hHead != NULL)//loop through every value in the list
	{
		ptr = hHead->next;
		DeleteSubSeq(hHead->sHead);//delete subsequences
		delete hHead;//delete head
		hHead = ptr;//head is now next value
	}
};
/*End: code taken from ptrfunc.cpp and updated*/

void SubSeqsList::AddSubSeq(int num)
	//pre: Linked list is sorted
	//post: All possible subsequences that can be formed with the given integer added to the list
	//keep list sorted
{
	if (Exists(num)) //Checks if there are nodes containing the value already in the linked list
	{
		cout << num << " is already in the list!" << endl;
		return;
	}
	//After if we know the number does not already exist in the linked list
	AddIndividualSub(num); //Adds a subsequence containing only the specified value to the linked list
	AddOrderedSubSeq(num); //Adds all possible ordered subsequences(size > 1) to the linked list
	cout << "Subsequence(s) containing " << num << " has/have been added" << endl;
};

bool SubSeqsList::Exists(int num) //Checks if there are nodes containing the value already in the linked list
{
	SubSeqHeadNode * ptr = hHead; //loop variable
	while (ptr != NULL && ptr->size <= 1)
	{
		if (ptr->sHead->value == num)
		{
			return true;
		}
		ptr = ptr->next;
	}
	return false;
};

void SubSeqsList::DisplayList() //Displays every value in the linked list
{
	if (IsEmpty()) //Checks if there are any nodes present in the linked list
	{
		cout << "List is empty!" << endl;
		return;
	}
	SubSeqHeadNode * ptr = hHead; //loop variable
	while (ptr != NULL) 
	{
		SubSeqNode * ptr2 = ptr->sHead; //loop variable for the values within the subsequences
		cout << ptr->size << " | ";
		while (ptr2->next != NULL)
		{
			cout << ptr2->value << " --> ";
			ptr2 = ptr2->next;
		}
		cout << ptr2->value << endl;
		ptr = ptr->next;
	}
};

/* Begin: code taken from ptrfunc.cpp and updated*/
void SubSeqsList::DeleteSubSeqHead(int num) 
	//pre: List is sorted
	//post: All subsequences containing given integer deleted, list is kept sorted
{
	if (!Exists(num)) //Checks if given value actuually exists in the list
	{
		cout << "There is no subsequence that contains " << num << " to be deleted" << endl;
		return;
	}
	SubSeqHeadNode * ptr = hHead; //loop variable
	while (ptr != NULL)
	{
		SubSeqHeadNode * temp = hHead; //pointer to be deleted
		if (Contains(ptr->sHead, num)) //Checks if the given value is in the subsequence
		{
			if (ptr == hHead) //if the subsequence to be deleted is the first subsequence
			{
				ptr = ptr->next;
				hHead = ptr; //move head to the next value
				DeleteSubSeq(temp->sHead);
				delete temp; 
			}
			else 
			{	
				while (temp->next != ptr) 
				{
					temp = temp->next;
				}
				//after while temp is the subsequence right before the ptr
				ptr = ptr -> next; //the subsequence to be deleted is now after temp and before ptr
				DeleteSubSeq(temp->next->sHead);
				delete temp->next;
				temp->next = ptr; //connect temp and ptr
			}
		}
		else 
		{
			ptr = ptr->next; //if value is not in subequence move to the next seubsequence
		}
	}
	cout << "All subsequence(s) containing " << num << " has/have been deleted" << endl;
};
/* End: code taken from ptrfunc.cpp and updated*/

/* Begin: code taken from ptrfunc.cpp and updated*/
void SubSeqsList::AddIndividualSub(int num)
	//pre: list is sorted
	//post: A subsequence containing only the specified value is added to the list, list is kept sorted
{
	SubSeqHeadNode * ptr = hHead; //loop variable
	SubSeqNode * newptr = new SubSeqNode(num, NULL); //create a new subsequence containing only specified value
	if (IsEmpty() || ptr->sHead->value > num) //Check if list is empty or our value is to be the first subsequence
	{
		hHead = new SubSeqHeadNode(1, newptr, ptr); //new head is our subsequence
		return;
	}
	while (ptr->next != NULL && ptr->next->size <= 1 && ptr->next->sHead->value < num)
	{
		ptr = ptr->next;
	}
	//after whle ptr is just before where our subsequence is to be inserted
	ptr->next = new SubSeqHeadNode (1, newptr, ptr->next); //insert subsequence 
	return;
};
/* End: code taken from ptrfunc.cpp and updated*/

void SubSeqsList::AddOrderedSubSeq(int num)  
	//pre: List is sorted
	//post: All possible subequences of size > 1 that can be formed with our given integer inserted into the linked list
	//keep list sorted
{
	SubSeqHeadNode * ptr = hHead; //loop variable
	int subseqsize; 
	SubSeqNode * nhead =  NULL; //head of our new subsequence
	while (ptr != NULL)
	{
		if (IsSubSeq(ptr->sHead, num))//checks given the existing values in a subsequence and specified integer if a new subsequence can be formed
		{
			subseqsize = 0;
			SubSeqNode * nhead = CreateSubSeq(ptr->sHead, num, subseqsize); //Creates a new subsequence and makes nhead the new head
			SubSeqHeadNode * ptr2 = ptr; //loop variable to find the point of insertion
			while (ptr2->next != NULL && ptr2->next->sHead == SmallerSubSeq(ptr2->next->sHead, ptr2->next->size, nhead, subseqsize))
			{
				ptr2 = ptr2->next;
			}
			//after while pointer is just before where subsequence is to be inserted
			ptr2->next = new SubSeqHeadNode (subseqsize, nhead, ptr2->next); //insert new subsequence
		}
		ptr = ptr->next;
	}	
};

bool SubSeqsList::IsSubSeq(SubSeqNode * head, int num)
	//checks given the existing values in a subsequence and specified integer if a new subsequence can be formed
{
	int bar = TailFinder(head); //finds the last value in the existing subsequencing and stores it as a threshold
	if (num > bar) //if the given integer is greater than the threshold value
	{
		return true; //New subsequence can be formed
	}
	return false; //Else a new subsequence cannot be formed cause it does not match appearance order
};

int SubSeqsList::TailFinder(SubSeqNode * head)
	//finds last value in a subsequence given the head node
{
	SubSeqNode * ptr = head;//loop variable
	while (ptr->next != NULL)
	{
		ptr = ptr ->next;
	}
	//after while ptr is at the node just before NULL
	return ptr->value;
};

/* Begin: code taken from ptrfunc.cpp and updated*/
void SubSeqsList::DeleteSubSeq(SubSeqNode * & head) 
	//Deletes every node in a subsequence
{
	SubSeqNode * temp = head;// loop variable
	while (head != NULL) 
	{
		temp = head->next;
		delete head;
		head = temp;
     }
};
/* End: code taken from ptrfunc.cpp and updated*/

bool SubSeqsList::Contains(SubSeqNode * head, int num)
	//Checks if a specific value is in a subsequence
{
	SubSeqNode * ptr = head;//loop variable
	while (ptr != NULL)
	{
		if  (ptr->value == num)
		{
			return true;
		}
		ptr = ptr->next;
	}
	return false;
};

SubSeqNode * SubSeqsList::CreateSubSeq(SubSeqNode * head, int num, int & size) 
	//Given the head of an existing subsequence
	//A new subsequence is created with the specified value inserted
{
	SubSeqNode * ptr = new SubSeqNode(head->value, NULL); //creates a new subsequence node with the same head value as the existing subsequqence
	SubSeqNode * nhead = ptr;//head of our new subsequence
	size = 1; //size of subsequence initialized as 1 since head value has already been inserted
	if (head->next != NULL) //if size of existing subsequence > 1
	{
		SubSeqNode * ptr2 = head->next;
		while (ptr2 != NULL)
		{
			ptr->next = new SubSeqNode(ptr2->value, NULL);
			size++; //increment size each time a value is inserted
			ptr = ptr->next;
			ptr2 = ptr2->next;
		}
		//after while all values from existing subsequence copied into new subsequence
	}
	ptr -> next = new SubSeqNode(num, NULL); //given integer inserted as last value of subsequence
	size++;//increment size since another value was inserted
	return nhead;//return head of subsequence
};

SubSeqNode * SubSeqsList::SmallerSubSeq(SubSeqNode * head1, int size1, SubSeqNode * head2, int size2)
	//Given two subsequences returns the smaller of the two
	//returns the first subsequence when both are equal
{
	SubSeqNode * ptr1 = head1;//loop variable for the first subsequence
	SubSeqNode * ptr2 = head2;//loop variable for the second subsequence
	if (size1 < size2) //Compares sizes
	{
		return head1;
	}
	else if (size2 < size1)
	{
		return head2;
	}
	//After if's confirmed that both subsequences have the same size
	for (int i = 0; i < size1; i++) //loops for the size of the subsequences
	{
		if (ptr1->value < ptr2 -> value)//compares values
		{
			return head1;
		}
		else if (ptr2->value < ptr1 -> value)
		{
			return head2;
		}
		ptr1 = ptr1 -> next;//Go to the next value in the subsequence
		ptr2 = ptr2 -> next;
	}
	return head1;
}









	
		