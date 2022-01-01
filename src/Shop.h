#ifndef JOINT_PROJECTS_SFML_SHOP_H
#define JOINT_PROJECTS_SFML_SHOP_H
/*
#include <iostream>

#include <windows.h>

#include <string.h>
*/
#include "Userdata.h"
#include <cstdint>
#include <cstdio>

//gathers variables from the clickergame.cpp
extern Userdata myscore;
extern int userInput;

class Shop
{
private:
	int PricePassiveMultiplier;	   //The price of Passive Multiplier
	int PriceClickerMuliplier;	   //The price of Clicker Multiplier
	double storeClickerMultiplier; //the Clicker Multiplier value in the store
	double storePassiveMuliplier;  //the Passive Multiplier value in the store
public:
	//constructor
	Shop()
	{
		PriceClickerMuliplier = 55;
		storeClickerMultiplier = 5;
		PricePassiveMultiplier = 55;
		storePassiveMuliplier = 2.5;
	};

	//shows the user the store menu
	void storeMenu()
	{
		while (1)
		{
			printf("You own %llu clicks\n", myscore.getUserClicks());
			printf("1) increase Clicker Multiplier by %.02f,For %o clicks\n", storeClickerMultiplier, PriceClickerMuliplier);
			printf("2) increase Passive Multiplier by %.02f,For %o clicks\n", storePassiveMuliplier, PricePassiveMultiplier);
			cout << "3)Exit the Store.\n"
				 << endl;
			cout << "Please select an option" << endl;
			cin >> userInput;
			if (userInput == 1 || userInput == 2 || userInput == 3 || userInput == 4)
			{
				break;
			}
		}
	};

	//If the user has more clicks than the price of the clicker mulitplier:
	//the user's click mulitplier is increase
	//the price and the Clicker multiplier at the store is increased
	//deduct the cost of the upgrade from the user's click score
	void increaseStoreClickerMultiplier()
	{
		unsigned long* dummy = (unsigned long*)malloc(sizeof(&myscore.getUserClicks));
		if (*dummy >= static_cast<unsigned long>(PriceClickerMuliplier))
		{
			myscore.addtoClickMulitplier(storeClickerMultiplier);
			PriceClickerMuliplier *= 1.5;
			storeClickerMultiplier *= 2.5;
			myscore.subtoUserClicks(PriceClickerMuliplier);
		}
		else
			cout << "Sorry, not enough clicks!!" << endl;
		delete dummy;
	};

	//If the user has more clicks than the price of the passive mulitplier:
	//the user's passive mulitplier is increase
	//the price and the passive multiplier at the store is increased
	//deduct the cost of the upgrade from the user's click score
	void increaseStorePassiveMuliplier()
	{
		unsigned long* dummy = (unsigned long*)malloc(sizeof(&myscore.getUserClicks));
		if (*dummy >= static_cast<unsigned long>(PricePassiveMultiplier))
		{
			myscore.addtoPassiveMulitplier(storePassiveMuliplier);
			PricePassiveMultiplier *= 1.5;
			storePassiveMuliplier *= 2;
			myscore.subtoUserClicks(PricePassiveMultiplier);
		}
		else
			cout << "Sorry, not enough clicks!!" << endl;

		delete dummy;
	};
};

#endif //JOINT_PROJECTS__SFML_SHOP_H