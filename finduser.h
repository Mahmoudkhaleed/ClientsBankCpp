#pragma once
#include "login.h"

namespace finduser
{
	void handleFindUser()
	{
		vector<login::stUser> usersArr = login::getUsersFromFile();
		login::stUser newUser;
		cout << "please enetr a username? ";
		cin >> newUser.userName;

		if (login::isUserNameExist(newUser))
		{
			printUserInfo(newUser);
		}
		else
		{
			cout << "The user with [" << newUser.userName << "] is not exist." << endl;
		}
	}

	void runFindUsers()
	{
		char state;
		do
		{
			system("cls");
			global::titleFrame("Find User", '-');
			handleFindUser();
			cout << "Do you want to find more users? Y/N ";
			cin >> state;
		} while (tolower(state) == 'y');
	}
}