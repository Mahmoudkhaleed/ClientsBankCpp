#pragma once
#include "global.h"
#include "login.h"
#include "adduser.h"
#include "deleteuser.h"
#include "updateuser.h"
#include "finduser.h"

namespace manageUsers
{
	enum userChoices 
	{
		UserList = 1, 
		AddNewUser = 2, 
		DeleteUser = 3, 
		UpdateUser = 4, 
		FindUser = 5, 
		MainMenu = 6
	};

	void printChoices()
	{
		system("cls");
		global::titleFrame("Manage Users", '=');

		cout << "\t[1] Show Users List." << endl;
		cout << "\t[2] Add New User." << endl;
		cout << "\t[3] Delete User." << endl;
		cout << "\t[4] Update User info." << endl;
		cout << "\t[5] Find User." << endl;
		cout << "\t[6] Main Menu." << endl;
		cout << global::makeLineOf(40, '=') << endl;
	}

	void printClientInfoInline(login::stUser &user)
	{
		cout << "| " << left << setw(24) << user.userName;
		cout << "| " << left << setw(20) << user.password;
		cout << "| " << left << setw(14) << user.permissions << endl;
	}

	void printUsersList()
	{
		system("cls");
		vector<login::stUser> usersArr = login::getUsersFromFile();
		cout << "\t\t\t\t\tUsers List (" << usersArr.size() << ") User/s" << endl;
		cout << global::makeLineOf(80) << endl << endl;
		cout << "| " << left << setw(3) << "I";
		cout << "| " << left << setw(24) << "User Name";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(14) << "Permission" <<endl;
		cout << global::makeLineOf(80) << endl << endl;
		for (int i = 0; i < usersArr.size(); i++)
		{
			cout << "| " << left << setw(3) << i + 1;
			printClientInfoInline(usersArr[i]);
		}
		cout << global::makeLineOf(80) << endl;
	}

	void systemPause()
	{
		cout << "click any key to go back...." << endl;
		system("pause>0");
	}
	
	void confirmChoice(userChoices choice)
	{
		switch (choice)
		{
		case UserList:
			printUsersList();
			systemPause();
				break;
		case AddNewUser:
			adduser::runAddNewUser();
			systemPause();
			break;
		case DeleteUser:
			deleteuser::runDeleteUser();
			systemPause();
			break;
		case UpdateUser:
			updateuser::updateUser();
			systemPause();
			break;
		case FindUser:
			finduser::runFindUsers();
			break;
		default:
			break;
		}
	}

	void runManageUsers()
	{
		userChoices choice;
		do
		{
			system("cls");
			printChoices();
			choice = (userChoices)global::readChoice(1, 6);
			confirmChoice(choice);
		} while (choice != userChoices::MainMenu);
	}

}