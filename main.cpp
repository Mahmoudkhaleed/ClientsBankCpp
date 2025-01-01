#pragma warning(disable : 4267)
#include <iostream>
#include "showclientlist.h"
#include "updateclient.h"
#include "deleteclient.h"
#include "addclient.h"
#include "findclient.h"
#include "transactions.h"
#include "login.h"
#include "manageusers.h"
#include "global.h"

using namespace std;

enum enMainMenuChoices
{
	Show = 1,
	Add = 2,
	Delete = 3,
	Update = 4,
	Find = 5,
	Trans = 6,
	ManageUsers = 7,
	Logout = 8
};

void runBankApp();

void printChoices()
{
	system("cls");
	global::titleFrame("Main Menu Screen", '=');

	cout << "\t[1] Show Clients List." << endl;
	cout << "\t[2] Add New Client." << endl;
	cout << "\t[3] Delete Client." << endl;
	cout << "\t[4] Update Client info." << endl;
	cout << "\t[5] Find Client." << endl;
	cout << "\t[6] Transactions." << endl;
	cout << "\t[7] Manage Users." << endl;
	cout << "\t[8] Logout." << endl;

	cout << global::makeLineOf(40, '=') << endl;
}

void pauseScreen()
{
	cout << "\npress any key to return back to the main menu...." << endl;
	system("pause>0");
}

void permissionDenied()
{
	system("cls");
	cout << "--------------------------------------" << endl;
	cout << "Access Denied" << endl;
	cout << "You don't have permission to do this," << endl;
	cout << "Please connect your admin." << endl;
	cout << "--------------------------------------" << endl;
}

void confirmChoice(enMainMenuChoices choice, login::stUser& inputUser)
{
	switch (choice)
	{
	case Show:
		if ((inputUser.permissions & 1) || inputUser.permissions == -1)
			showlist::clientFrameToPrint();
		else
			permissionDenied();
		pauseScreen();
		break;
	case Add:
		if ((inputUser.permissions & 2) == 2 || inputUser.permissions == -1)
			addclient::addClients();
		else
			permissionDenied();
		pauseScreen();
		break;
	case Delete:
		if ((inputUser.permissions & 4) == 4 || inputUser.permissions == -1)
			deleteclient::deleteClient();
		else
			permissionDenied();
		pauseScreen();
		break;
	case Update:
		if ((inputUser.permissions & 8) == 8 || inputUser.permissions == -1)
			update::updateClient();
		else
			permissionDenied();
		pauseScreen();
		break;
	case Find:
		if ((inputUser.permissions & 16) == 16 || inputUser.permissions == -1)
			find::findClient();
		else
			permissionDenied();
		pauseScreen();
		break;
	case Trans:
		if ((inputUser.permissions & 32) == 32 || inputUser.permissions == -1)
			transaction::runTransactionMenu();
		else
		{
			permissionDenied();
			pauseScreen();
		}
		break;
	case ManageUsers:
		if ((inputUser.permissions & 64) == 64 || inputUser.permissions == -1)
			manageUsers::runManageUsers();
		else
		{
			permissionDenied();
			pauseScreen();
		}
		break;
	case Logout:
		runBankApp();
		break;
	default:
		cout << "\npress any key to exit...." << endl;
		return;
	}
}

void openApp(login::stUser &inputUser)
{
	enMainMenuChoices choice;
	do
	{
		system("cls");
		printChoices();
		choice = (enMainMenuChoices)global::readChoice(1, 8);
		confirmChoice(choice, inputUser);
	} while (true);
}

void runBankApp()
{
	system("cls");
	login::stUser inputUser;
	global::titleFrame("login screen", '-');
	inputUser = login::readUserAndPass();

	while (!login::isUserExist(inputUser))
	{
		system("cls");
		global::titleFrame("login screen", '-');
		cout << "Username or password is not correct, please try again!" << endl;
		inputUser = login::readUserAndPass();
	}

	openApp(inputUser);
}


int main()
{
	runBankApp();
	system("pause>0");
	return 0;
}