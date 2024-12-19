#pragma once
#include "global.h"

namespace find
{
	void searchForClient()
	{
		global::stClient client;
		vector<global::stClient> arr = global::readCLientsFileToArray();
		string number;
		cout << "Enter an account number? ";
		cin >> number;

		if (global::findClient(arr, number, client))
		{
			global::printClientCard(client);
		}
		else
		{
			cout << "the account with " << number << " account number is not exist\n";
		}
	}

	void findClient()
	{
		char state;
		do
		{
			system("cls");
			global::titleFrame("Find Client");
			searchForClient();
			cout << "Do you want to search for more clients? Y/N? ";
			cin >> state;
		} while (state == 'y' || state == 'Y');
	}
}