/****************************************************************************************
Title: A C++ Class for creating and using a Wallet Object
Author: Victor Oluwalonimi Taiwo
Student ID: 28579
Date: 22/04/2021
Any known bugs: none
****************************************************************************************/




#ifndef _WALLET_H
#define _WALLET_H

#include <iostream>
#include <string>
using namespace std;

struct Money
{
	string currency; 
	double amount; 

	Money() //default constructor
	{
		currency = "";
		amount = 0;
	}
	Money(const string & name, double amount) //parametric constructor of money struct
		:currency(name), amount(amount)
	{}
};

class Wallet
{
	private:
		Money* accounts; //pointer to dynamic array of all currencies in wallet
		int size; //size of dynamic array
	public:
		Wallet (); //default constructor 
		Wallet (const Wallet &); //deep copy constructor
		~Wallet (); //destructor
		Wallet operator + (Money rhs) const; //increment wallet value for a single specified currency
		Wallet operator - (Money rhs) const; //decrement wallet value for a single specified currency
		const Wallet & operator = (const Wallet & rhs); //clears lhs wallet and updates with contents of rhs
		const Wallet & operator += (const Wallet & rhs); //increments lhs wallet by content of rhs
		int getUniqueCurrency (const Wallet & rhs) const; //determines number of unique currency between two wallets
		bool Equals (const Wallet & wallet) const; //checks for equality of two wallets
		bool operator >=  (Money rhs) const;
		int getCurrencyIndex (Money) const; //retrieves index for a currency in a wallet,
									        //returns -1 if wallet does not contain such currency
		string tostring () const; //returns string equivalent of wallet
		void TransferCurrencies(const Wallet &); //Transfers all currencies from specified Wallet into caller Wallet
		void ClearWallet (); //clears wallet and reinitializes to size 0
};

ostream & operator << (ostream & os, const Wallet & wallet); //converts wallet to an output stream object
Wallet operator + (const Wallet & lhs, const Wallet & rhs); //returns new wallet that is a combination of the lhs and rhs
bool operator ==  (const Wallet & lhs, const Wallet & rhs);//checks equality of two wallet objects
bool operator <=  (Money lhs, const Wallet& rhs);
string MoneytoString (Money);
#endif