/******************************************************************************
Title: A C++ class for Displaying All Ordered Subsequences with a Hybrid Linked List Structure
Author: Victor Oluwalonimi Taiwo
Student ID: 28579
Date: 29/3/2021
Any known bugs: none
References: ptrfunc.cpp
******************************************************************************/


#ifndef _taiwovictor_Taiwo_VictorOluwalonimi_hw3_SubSeqsListClass_H
#define _taiwovictor_Taiwo_VictorOluwalonimi_hw3_SubSeqsListClass_H

#include <string>
using namespace std;

struct SubSeqNode //struct for making linked list of subsequences
{
	int value;
	SubSeqNode * next;

	SubSeqNode::SubSeqNode() //default constructor
	{}

	SubSeqNode::SubSeqNode (int info, SubSeqNode * p) //Parametric constructor 
		: value(info), next(p)
	{};
};
struct SubSeqHeadNode //struct for making a linked list of the head of ordered subsequences
{
	int size; // number of elements in the subsequence
	SubSeqNode * sHead; // head of the subsequence list
	SubSeqHeadNode * next; 
	
	SubSeqHeadNode::SubSeqHeadNode() //default constructor
	{}

	SubSeqHeadNode::SubSeqHeadNode(int s, SubSeqNode * p, SubSeqHeadNode * f) //Parametric constructor 
		: size(s), sHead(p), next(f)
	{};
};
//NOTE: Everytime linked list is mentioned in comments I am referring to the linked list of head nodes. 
class SubSeqsList
{
private:
	SubSeqHeadNode * hHead; //head of the list of heads of ordered subsequences 
	void AddIndividualSub(int); //Adds a subsequence with only one node to the linked list
	void AddOrderedSubSeq(int); //Given an integer value finds all possible subsequences of size>1 and adds to our linked list
	//below functions all perform operations on the subsequences and not the linked list of head nodes itself
	bool IsSubSeq (SubSeqNode *, int); //Checks if a new ordered subsequence can be made given an integer value and the head of an ordered subsequence
	int TailFinder (SubSeqNode *); //returns the tail value of a subsequence given the head of that subsequence
	void DeleteSubSeq(SubSeqNode * &); //Deletes every node within a subsequence
	bool Contains(SubSeqNode *,int); //Checks if there is a node containing a specified value in the subsequence
	SubSeqNode * CreateSubSeq(SubSeqNode * head, int, int&); //Creates a new ordered subsequence
	SubSeqNode * SmallerSubSeq(SubSeqNode *, int, SubSeqNode * , int); //finds the smaller of two nodes
public:
	SubSeqsList(); //default constructor that creates an empty list
	bool IsEmpty();//Checks if there is any node in the linked list
	void Clear(); //Deletes every node in the linked list
	void AddSubSeq(int); //Adds all possible subsequences that can be formed from the given integer value to the linked list
	bool Exists(int); //Checks if a given integer value exists in the linked list
	void DisplayList(); //Displays every value in the linked list
	void DeleteSubSeqHead(int); //Deletes every subsequence containing a given integer value in the linked list 

};

#endif
