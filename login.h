#pragma once
#include "global.h"

namespace login
{
	struct stUser
	{
		string userName;
		string password;
		int permissions;
	};

	stUser readUserAndPass()
	{
		stUser user;
		cout << "Enter Username: ";
		cin >> user.userName;
		cout << "Enter Password: ";
		cin >> user.password;
		return user;
	}

	stUser getUserDataFromLine(string str)
	{
		vector<string> arr = global::convertStrLineToArrOfStrs(str);
		stUser user;
		user.userName = arr[0];
		user.password = arr[1];
		user.permissions = stoi(arr[2]);
		return user;
	}

	vector<stUser> getUsersFromFile()
	{
		vector<stUser> users;
		fstream usersFile;
		usersFile.open("users.txt", ios::in);
		if (usersFile.is_open())
		{
			string str;
			while (getline(usersFile, str))
			{
				users.push_back(getUserDataFromLine(str));
			}
			usersFile.close();
		}
		return users;
	}

	bool isUserExist(stUser &inputUser)
	{
		vector<stUser> users = getUsersFromFile();
		for (stUser user : users)
		{
			if (inputUser.userName == user.userName && inputUser.password == user.password)
			{
				inputUser = user;
				return 1;
			}
		}
		return 0;
	}

	bool isUserNameExist(login::stUser &inputUser)
	{
		vector<login::stUser> users = login::getUsersFromFile();
		for (login::stUser user : users)
		{
			if (inputUser.userName == user.userName)
			{
				inputUser = user;
				return 1;
			}
		}
		return 0;
	}

	string convertRecordToLine(stUser& user, string sep = "#//#")
	{
		string str;
		str += user.userName + sep;
		str += user.password + sep;
		str += to_string(user.permissions);
		return str;
	}

	void printUserInfo(stUser user)
	{
		cout << "\nThe following user details: " << endl;
		cout << "------------------------------" << endl;
		cout << "Username: " << user.userName << endl;
		cout << "Password: " << user.password << endl;
		cout << "Permission: " << user.permissions << endl;
		cout << "------------------------------" << endl;
	}

	void updateUsersFile(vector<stUser>& arr)
	{
		fstream usersFile;
		usersFile.open("users.txt", ios::out);
		if (usersFile.is_open())
		{
			for (stUser& user : arr)
			{
				usersFile << convertRecordToLine(user) << endl;
			}
			usersFile.close();
		}
	}

	void handlePermissionChoice(stUser& newUser, int choiceNumber, string choiceName)
	{
		char yOrN;
		do
		{
			cout << choiceName << "? Y/N ";
			cin >> yOrN;
		} while (tolower(yOrN) != 'y' && tolower(yOrN) != 'n');

		if (tolower(yOrN) == 'y')
			newUser.permissions = (newUser.permissions | choiceNumber); // 1
	}

	void getPermission(stUser& newUser)
	{
		newUser.permissions = 0;
		handlePermissionChoice(newUser, 1, "Show Clients List");
		handlePermissionChoice(newUser, 2, "Add New Client");
		handlePermissionChoice(newUser, 4, "Delete Client");
		handlePermissionChoice(newUser, 8, "Update Client info");
		handlePermissionChoice(newUser, 16, "Find Client");
		handlePermissionChoice(newUser, 32, "Transactions");
		handlePermissionChoice(newUser, 64, "Manage Users");
	}

}