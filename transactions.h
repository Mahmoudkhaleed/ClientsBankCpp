#pragma once
#include "global.h"

namespace transaction
{
	enum enMenuTwoChoices { Deposit = 1, Withdraw = 2, TotalBalance = 3, MainMenu = 4 };

	void updateClientBalance(global::stClient& client, int deposit)
	{

		client.accBalance = to_string(stoi(client.accBalance) + deposit);
	}

	void updateClientsArr(global::stClient& client, vector<global::stClient>& arr)
	{
		for (global::stClient& c : arr)
		{
			if (client.accNumber == c.accNumber)
			{
				c = client;
				break;
			}
		}
	}

	void confirmTransaction(global::stClient& client, vector<global::stClient>& arr)
	{
		char state;
		cout << "Are you sure you want to perform this transaction? Y/N ";
		cin >> state;
		if (tolower(state) == 'y')
		{
			updateClientsArr(client, arr);
			cout << "The account balance is now: " << client.accBalance << endl;
			global::updateClientsFile(arr);
		}
	}

	int readNumber(string str)
	{
		int number;
		cout << "\n" << str;
		cin >> number;
		return number;
	}

	void checkNumberAndProceed(global::stClient& client, vector<global::stClient>& arr, int number)
	{
		updateClientBalance(client, number);
		confirmTransaction(client, arr);
		cout << "\nPress any key to go back to transction screen...\n";
		system("pause>0");
	}

	void depositInClientAccount()
	{
		system("cls");
		global::titleFrame("Deposit screen");

		string accNumber = global::readStr("Please enter an account number? ");
		vector<global::stClient> arr = global::readCLientsFileToArray();
		global::stClient client;
		while (!global::findClient(arr, accNumber, client))
		{
			cout << "CLient with " << accNumber << " account number is not exist" << endl;
			accNumber = global::readStr("Please enter an account number? ");
		}

		global::printClientCard(client);
		int number = readNumber("please enter a deposit number? ");
		checkNumberAndProceed(client, arr, number);
	}

	void withdrawFromClientAcc()
	{
		system("cls");
		global::titleFrame("Withdraw screen");

		string accNumber = global::readStr("Please enter an account number? ");
		vector<global::stClient> arr = global::readCLientsFileToArray();
		global::stClient client;

		while (!global::findClient(arr, accNumber, client))
		{
			cout << "CLient with " << accNumber << " account number is not exist" << endl;
			accNumber = global::readStr("Please enter an account number? ");
		}

		global::printClientCard(client);
		int number = readNumber("please enter a number to withdraw? ");
		while (stoi(client.accBalance) < number)
		{
			cout << "You can only withdraw up to " << client.accBalance << endl;
			number = readNumber("please enter a number to withdraw? ");
		}
		checkNumberAndProceed(client, arr, -number);
	}

	void printClientInfoInline(global::stClient& client)
	{
		cout << "| " << left << setw(20) << client.accNumber;
		cout << "| " << left << setw(30) << client.name;
		cout << "| " << left << setw(30) << client.accBalance << endl;
	}

	void printTotalBalances()
	{
		system("cls");
		int totalBalances = 0;
		vector<global::stClient> arr = global::readCLientsFileToArray();
		cout << "\t\t\t\t\tClient List (" << arr.size() << ") Client/s" << endl;
		cout << global::makeLineOf(95) << endl << endl;
		cout << "| " << left << setw(3) << "I";
		cout << "| " << left << setw(20) << "Account Number";
		cout << "| " << left << setw(30) << "Client Name";
		cout << "| " << left << setw(30) << "Balance" << endl;
		cout << global::makeLineOf(95) << endl << endl;
		for (int i = 0; i < arr.size(); i++)
		{
			cout << "| " << left << setw(3) << i + 1;
			printClientInfoInline(arr[i]);
			totalBalances += stoi(arr[i].accBalance);
		}
		cout << global::makeLineOf(95) << endl;
		cout << "\t\t\t\t\tTotal Balances = " << totalBalances << endl;
		cout << "\nPress any key to go back to transction screen...\n";
		system("pause>0");
	}

	void printChoices()
	{
		system("cls");
		global::titleFrame("Transactions Menu Screen", '=');

		cout << "\t[1] Deposit." << endl;
		cout << "\t[2] Withdraw." << endl;
		cout << "\t[3] Total Balance." << endl;
		cout << "\t[4] Main Menu." << endl;
		cout << global::makeLineOf(40, '=') << endl;
	}

	void confirmChoice(enMenuTwoChoices choice)
	{
		switch (choice)
		{
		case Deposit:
			depositInClientAccount();
			break;
		case Withdraw:
			withdrawFromClientAcc();
			break;
		case TotalBalance:
			printTotalBalances();
			break;
		default:
			break;
		}
	}

	void runTransactionMenu()
	{
		enMenuTwoChoices choice;
		do
		{
			system("cls");
			printChoices();
			choice = (enMenuTwoChoices)global::readChoice(1, 4);
			confirmChoice(choice);
		} while (choice != enMenuTwoChoices::MainMenu);
	}

}