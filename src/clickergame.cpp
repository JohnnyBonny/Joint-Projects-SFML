#include "Shop.h"
#include "Userdata.h"
#include <conio.h>
#include <iostream>
#include <string.h>
#include <time.h>
#include <windows.h>

#define JOINT_PROJECTS_SFML_CLICKERGAME_CPP

using namespace std;
/*
Userdata myscore = Userdata();

int userInput;

Shop userShop = Shop();

int numberOfClicks = 0;

void executeClicks()
{
	while (1)
	{
		if (GetAsyncKeyState(0x01))
		{ //left mouse key
			numberOfClicks++;
			cout << "Left Mkey";

			Sleep(100);
			To check that it doesnt go the max int
            if(numberOfClicks + (myscore.getClickMulitplier()) >= INT_MAX){
            }

}
else if (GetAsyncKeyState(0x09)) //tab
	break;
}
getch();
}

void menu()
{
	while (1)
	{
		cout << "1)Get upgrades at the shop" << endl;
		cout << "2)Show Your Clicks" << endl;
		cout << "3)CLICK!!!" << endl;
		cout << "4)Exit Game" << endl;
		cout << "Please select an option" << endl;
		cin >> userInput;
		if (userInput == 1 || userInput == 2 || userInput == 3 || userInput == 4)
		{
			break;
		}
	}
}

void clickerGame()
{
	cout << "Welcome to the Clicker Game" << endl;

    while(1){
        menu();
        if(userInput == 1){
            userShop.shopMenu();

        }
    }

}

int main()
{
	clock_t start = clock();
	BigInt x("123472389473473897491");
	myscore.addtoUserClicks(x);
	userShop.increaseStorePassiveMuliplier();
	userShop.increaseStoreClickerMultiplier();
	printf("My clicksMultiplier:%.02f\n", myscore.getClickMulitplier());
	printf("My passiveMultiplier:%.02f\n", myscore.getPassiveMultiplier());
	clock_t end = clock();
	int elapsed = int(double(end - start) / CLOCKS_PER_SEC);
	printf("\nTime measured: %i seconds.\n", elapsed);
	return 0;
}
*/