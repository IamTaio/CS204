/****************************************************************************************
Title: A C++ Class for creating and using a Wallet Object
Date: 22/04/2021
Any known bugs: none
****************************************************************************************/



#include <iostream>
#include <sstream>
#include "WalletClass.h"
using namespace std;

Wallet::Wallet() //Default constructor
{
	accounts = NULL;
	size = 0;
}

Wallet::~Wallet() 
	//Destructor
{
	
	if (size != 0)
	{
		delete [] accounts;
		size = 0;
	}
}


void Wallet::TransferCurrencies(const Wallet & Wallet2)
//not an assignment operator
//pre: lhs Wallet is of a size bigger than/equal to Wallet 2
//expected to be used to fill an empty wallet of bigger or equal size
//post: all currencies in Wallet 2 are now in our Wallet
{

	if (size < Wallet2.size) //A smaller Wallet can not be filled
	{
		cout << "Trying to transfer currencies from a bigger account to a smaller account" << endl;
		return;
	}
	for (int i = 0; i < Wallet2.size; i++) //iteratively transfers money from Wallet 2 
	{
		accounts[i].amount = Wallet2.accounts[i].amount;
		accounts[i].currency = Wallet2.accounts[i].currency;
	}
}

Wallet::Wallet(const Wallet & copy) //Copy constructor
{
	
	accounts = new Money[copy.size];
	size = copy.size;
	TransferCurrencies(copy);
	
}

int Wallet::getCurrencyIndex(Money currency) const 
	//returns the index for specified currency
	//returns -1 if currency does not exist in Walllet
{
	if (size == 0 || accounts == NULL)
	{
		return -1; //Always returns -1 for an empty Wallet
	}
	for (int i = 0;  i < size; i++)
	{
		if (currency.currency == accounts[i].currency) //find matching currency
		{
			return i; //return index
		}
	}
	return -1;
}



Wallet Wallet::operator + (Money rhs) const
	//increments Wallet by specified money 
{
	if (getCurrencyIndex(rhs) == -1) //If currency does not already exist in Wallet
	{
		Wallet result; //New Wallet object
		int x = size; //index variable
		result.accounts = new Money[size+1]; //initialize result as a wallet with extra array memory for another Money node
		result.size = size;
		if (result.accounts == NULL)
			//rare case that not enough memory for allocation, terminates program
		{
			cout << "insufficient memory for task" << endl;
			exit(1);
		}
		result.accounts[x].amount = rhs.amount; //Add Money to the last index of the array
		result.accounts[x].currency = rhs.currency;
		result.size += 1;
		result.TransferCurrencies(*this); //Fill all other index with the currency in original wallet
		return result;
	}
	//for the case that Currency already in Wallet
	Wallet result (*this);
	int index = getCurrencyIndex(rhs);
	result.accounts[index].amount += rhs.amount;
	return result;
}

Wallet Wallet::operator - (Money rhs) const
{
	if (getCurrencyIndex(rhs) == -1) //If Currency not in Wallet just return lhs
	{
		return *this;
	}
	//Currency is in Wallet
	int index = getCurrencyIndex(rhs);
	if (accounts[index].amount < rhs.amount) //if amount in Wallet is insufficient return lhs
	{
		return *this;
	}
	else if (accounts[index].amount == rhs.amount) //if amount in Wallet is equal, then remove currency from Wallet
	{
		Wallet result;
		result.accounts = new Money[size-1]; //Create new Wallet with size-1 (Currency will be deleted)
		result.size = size - 1;
		int i = 0;
		while (i < index)
		{
			result.accounts[i].amount = accounts[i].amount;
			result.accounts[i].currency = accounts[i].currency;
			i++;
		}
		//After loop all Currency before specified has been added to new Wallet
		i++; //Skip Currency index
		while (i < size)
		{
			result + accounts[i];
			i++;
		}
		//After loop all Currency after specified has been added to new Wallet
		return result;
	}
	//Case that amount in Wallet is greater than rhs
	Wallet result (*this);
	result.accounts[index].amount -= rhs.amount;
	return result; 
}

bool Wallet::Equals (const Wallet & rhs) const //Return true if both Wallets are equal, return false otherwise
{
	if (size == 0 && rhs.size == 0)
	{
		return true;
	}
	if (size != rhs.size) //If Size differs return false
	{
		return false;
	}
	for (int i=0; i < size; i++)
	{
		int index = getCurrencyIndex(accounts[i]);
		if (index == -1) //If there is a currency in lhs not in right return false
		{
			return false;
		}
		if (accounts[i].amount != rhs.accounts[index].amount) 
			//If there is a currency in lhs with different amount than right return false
		{
			return false;
		}
	}
	return true;
}

const Wallet & Wallet::operator = (const Wallet & rhs)
{
	if (!Equals(rhs))
	{
		ClearWallet();
		accounts = new Money[rhs.size];
		size = rhs.size;
		TransferCurrencies(rhs);
	}
	return *this;
}

int Wallet::getUniqueCurrency (const Wallet & rhs) const
	//Finds number of currencies in rhs that are not in lhs
{
	int count = 0;
	if (size == 0 )
	{
		return rhs.size;
	}
	else if (rhs.size == 0)
	{
		return 0;
	}
	for (int i = 0; i < rhs.size; i++)
	{
		if (getCurrencyIndex(rhs.accounts[i]) == -1)
		{
			count++;
		}
	}
	return count;
}

const Wallet & Wallet::operator += (const Wallet & rhs)
{
	//increment lhs by rhs
	Wallet result;
	for (int i = 0; i < rhs.size; i++) //go through rhs iteratively and add Money to lhs
	{
		*this = operator + (rhs.accounts[i]);
	}
	return *this;
}

void Wallet::ClearWallet()
{
	//Delete all currency in Wallet and reinitialize to NULL
	if (size != 0 || accounts != NULL)
	{
		delete [] accounts;
		size = 0;
		accounts = NULL;
	}
}

bool Wallet::operator >= (Money rhs) const
{
	//Check if lhs greater than rhs
	int index = getCurrencyIndex(rhs);
	if (index == -1)
	{
		return false;
	}
	if (accounts[index].amount < rhs.amount)
	{
		return false;
	}
	return true;
}

string MoneytoString (Money TobeDisplayed)
{
	//Returns string equivalent of a Money object
	ostringstream output;
	output << TobeDisplayed.currency << " " << TobeDisplayed.amount;
	return output.str();
}


string Wallet::tostring () const
{
	//Return string equivalent of a Wallet
	if (size == 0)
	{
		return "";
	}
	string WalletDetails;
	int i = 0;
	for (i = 0; i < size-1; i++)
	{
		WalletDetails += MoneytoString(accounts[i]) + " - ";
	}
	i = size-1;
	WalletDetails += MoneytoString(accounts[i]);
	return WalletDetails;
}


ostream & operator << (ostream & os, const Wallet & wallet)
{
	//Returns output stream of Wallet
	os << wallet.tostring();
	return os;
}

Wallet operator + (const Wallet & lhs, const Wallet & rhs)
{
	//Sums two Wallets
	Wallet Result;
	Result = lhs;
	Result += rhs;
	return Result;
}

bool operator ==  (const Wallet & lhs, const Wallet & rhs)
{
	//Checks equality of two Wallets
	return lhs.Equals(rhs);
}

bool operator <=  (Money lhs, const Wallet& rhs)
{
	if (rhs >= lhs)
	{
		return true;
	}
	return false;
}




	



	