#include <iostream>
#include "taiwovictor_Taiwo_VictorOluwalonimi_hw6_PlayerClass.h"
#include "taiwovictor_Taiwo_VictorOluwalonimi_hw6_BoardClass.h"

using namespace std;

//Constructor
template<class itemType>
Player<itemType>::Player(Board<itemType> & board) 
	: myboard(board)
{
	score = 0;
}

template<class itemType>
bool Player<itemType>::validMove(int row, int col) const
{
	return myboard.isValid(row, col);
}

template<class itemType>
itemType Player<itemType>::openCard(int row, int col) 
{
	return myboard.openCard(row, col);
}

template<class itemType>
void Player<itemType>::increaseNumberOfSuccess()
{
	score = score + 1;
}

template<class itemType>
int Player<itemType>::getNumberOfSuccess() const
{
	return score;
}

