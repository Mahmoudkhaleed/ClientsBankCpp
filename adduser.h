#pragma once
#include "login.h"
namespace adduser {


	void addNewUser()
	{
		vector<login::stUser> usersArr = login::getUsersFromFile();
		login::stUser newUser;
		cout << "Enetr username? ";
		cin >> newUser.userName;
		if (!login::isUserNameExist(newUser))
		{
			cout << "Enetr password? ";
			cin >> newUser.password;
			char state;
			cout << "Do you want to give full access? Y/N ";
			cin >> state;
			if (tolower(state) == 'y')
				newUser.permissions = -1;
			else
			{
				cout << "do you want to have access to: " << endl << endl;
				login::getPermission(newUser);
			}

			usersArr.push_back(newUser);
			login::updateUsersFile(usersArr);
			cout << "User is added successfully, ";
			
		}
		else
		{
			cout << "The user with [" << newUser.userName << "] is already exist, ";
		}

	}

	void runAddNewUser()
	{
		char state;
		do
		{
			system("cls");
			global::titleFrame("Add New User", '-');
			addNewUser();
			cout << "Do you want to add more users? Y/N ";
			cin >> state;
		} while (tolower(state) == 'y');
	}
	
}