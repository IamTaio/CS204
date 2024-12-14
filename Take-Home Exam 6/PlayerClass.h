/****************************************************************************************
Title: A C++ Class for creating players for a Board game
Author: Victor Oluwalonimi Taiwo
Student ID: 28579
Date: 9/05/2021
Any known bugs: none
****************************************************************************************/



#ifndef _PLAYER_H
#define _PLAYER_H
#include "BoardClass.h"
using namespace std;

template<class itemType>
class Player
{
	private:
		Board<itemType> & myboard;
		int score;
	public:
		Player();
		Player(Board<itemType>&);
		itemType openCard(int row, int col);
		bool validMove(int row, int col) const;
		void increaseNumberOfSuccess();
		int getNumberOfSuccess() const;
};

#include "taiwovictor_Taiwo_VictorOluwalonimi_hw6_PlayerClass.cpp"

#endif