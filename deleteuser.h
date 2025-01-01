#pragma once
#include "login.h"

namespace deleteuser
{
	void varifyDelete(vector<login::stUser>& usersArr, vector<login::stUser> &newUsersArr, login::stUser &inputUser)
	{
		printUserInfo(inputUser);
		char state;
		cout << "Are you sure you want to delete? Y/N ";
		cin >> state;
		if (tolower(state) == 'y')
		{
			for (login::stUser& user : usersArr)
			{
				if (user.userName != inputUser.userName)
				{
					newUsersArr.push_back(user);
				}
			}
			login::updateUsersFile(newUsersArr);
			cout << "[" << inputUser.userName << "] User was deleted successfully!" << endl;
		}
	}
	void handleDeleteUser(vector<login::stUser> &usersArr)
	{
		vector<login::stUser> newUsersArr;
		login::stUser inputUser;

		cout << "Enter a username to delete? ";
		cin >> inputUser.userName;

		if (inputUser.userName == "admin")
		{
			cout << "the admin user cannot be deleted!" << endl;
			handleDeleteUser(usersArr);
		} 
		else
		{
			if (login::isUserNameExist(inputUser))
			{
				varifyDelete(usersArr, newUsersArr, inputUser);
			}
			else
			{
				cout << "The [" << inputUser.userName << "] is not exist!" << endl;
				handleDeleteUser(usersArr);
			}
		}		
	}
	void runDeleteUser()
	{
		system("cls");
		global::titleFrame("Delete User", '-');
		vector<login::stUser> usersArr = login::getUsersFromFile();

		handleDeleteUser(usersArr);

	}
}