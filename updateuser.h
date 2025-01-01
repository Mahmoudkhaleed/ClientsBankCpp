#pragma once
#include "login.h"

namespace updateuser
{
	void handleUpdateUser(vector<login::stUser> &usersArr, login::stUser &newUser)
	{
		cout << "Enetr a password? ";
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

		for (login::stUser& user : usersArr)
		{
			if (user.userName == newUser.userName)
			{
				user = newUser;
				break;
			}
		}
		login::updateUsersFile(usersArr);
		
	}

	void updateUser()
	{
		vector<login::stUser> usersArr = login::getUsersFromFile();
		login::stUser newUser;
		cout << "please enetr a username? ";
		cin >> newUser.userName;
		if (login::isUserNameExist(newUser))
		{
			printUserInfo(newUser);
			char state;
			cout << "Are you sure you want to update? Y/N ";
			cin >> state;
			if (tolower(state) == 'y')
			{
				handleUpdateUser(usersArr, newUser);
				cout << "User is updated successfully, ";
			}
		}
		else
		{
			cout << "The user with [" << newUser.userName << "] is not exist" << endl;
		}
	}

	void runUpdateUsers()
	{
		char state;
		do
		{
			system("cls");
			global::titleFrame("Update User", '-');
			updateUser();
			cout << "Do you want to update more users? Y/N ";
			cin >> state;
		} while (tolower(state) == 'y');
	}

}