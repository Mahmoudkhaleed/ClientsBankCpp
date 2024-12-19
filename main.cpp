#include <iostream>
#include "showlist.h"
#include "updateclient.h"
#include "deleteclient.h"
#include "addclient.h"
#include "findclient.h"
#include "global.h"

using namespace std;

enum enChoises {Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5, Exit = 6};


void printChoices()
{
	system("cls");
	global::titleFrame("Main Menu Screen", '=');

	cout << "\t[1] Show Clients List." << endl;
	cout << "\t[2] Add New Client." << endl;
	cout << "\t[3] Delete Client." << endl;
	cout << "\t[4] Update Client info." << endl;
	cout << "\t[5] Find Client." << endl;
	cout << "\t[6] Exit." << endl;
	cout << global::makeLineOf(40, '=') << endl;
}

enChoises readChoice()
{
	int number;
	do
	{
		system("cls");
		printChoices();
		cout << "What do you want to do? [1->6] ";
		cin >> number;
	} while (number > 6 || number < 1);
	return (enChoises)number;
}

void confirmChoice(enChoises choice)
{
	switch (choice)
	{
	case Show:
		showlist::clientFrameToPrint();
		break;
	case Add:
		addclient::addClients();
		break;
	case Delete:
		deleteclient::deleteClient();
		break;
	case Update:
		update::updateClient();
		break;
	case Find:
		find::findClient();
		break;
	default:
		cout << "\npress any key to exit...." << endl;
		return;
	}
	cout << "\npress any key to return back to the main menu...." << endl;
	system("pause>0");
}

void runBankApp()
{
	enChoises choice;
	do
	{
		choice = readChoice();
		confirmChoice(choice);
	} while (choice != enChoises::Exit);
}

int main()
{
	runBankApp();
	system("pause>0");
	return 0;
}