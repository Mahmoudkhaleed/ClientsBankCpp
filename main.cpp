#pragma warning(disable: 4267)
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;


struct stClient
{
	string userName;
	string pinCode;
	string fullName;
	string phoneNumber;
	string deposit;
};

stClient inputedClient;

enum enMainMenuChoices
{
	QuickWithdraw = 1,
	NormalWithdraw = 2,
	Deposit = 3,
	CheckBalance = 4,
	Logout = 5
};

enum enQuickWithdrawChoices
{
	W20 = 1,
	W50 = 2,
	W100 = 3,
	W200 = 4,
	W400 = 5,
	W600 = 6,
	W800 = 7,
	W1000 = 8,
	Exit = 9
};

stClient readUserAndPass()
{
	stClient client;
	cout << "Enter username? ";
	cin >> client.userName;
	cout << "Enter password? ";
	cin >> client.pinCode;
	return client;
}

vector<string> convertStrLineToArr(string line, string sep = "#//#")
{
	vector<string> arr;
	int pos;
	while ((pos = line.find(sep)) != string::npos)
	{
		arr.push_back(line.substr(0, pos));
		line.erase(0, pos + sep.length());
	}
	arr.push_back(line);
	return arr;
}

string convertClientToString(stClient client, string sep = "#//#")
{
	string str;
	str += client.userName + sep;
	str += client.pinCode + sep;
	str += client.fullName + sep;
	str += client.phoneNumber + sep;
	str += client.deposit;
	return str;
}

void writeClientsToFile(vector<stClient> &clients)
{
	fstream clientsFile;
	clientsFile.open("../Bank project 3/clients.txt", ios::out);
	if (clientsFile.is_open())
	{
		for (stClient &client : clients)
		{
			clientsFile << convertClientToString(client) << endl;
		}
		clientsFile.close();
	}
}

vector<stClient> getFileClients();

void updateCLientFile(stClient& clientToUpdate)
{
	vector<stClient> clients = getFileClients();
	for (stClient &client : clients)
	{
		if (client.userName == clientToUpdate.userName)
		{
			client = clientToUpdate;
			writeClientsToFile(clients);
			break;
		}
	}
}

stClient getClientStructFromArr(string str)
{
	vector<string> arr = convertStrLineToArr(str);
	stClient client;
	client.userName = arr[0];
	client.pinCode = arr[1];
	client.fullName = arr[2];
	client.phoneNumber = arr[3];
	client.deposit = arr[4];
	return client;
}

vector<stClient> getFileClients()
{
	vector<stClient> clientsArr;
	fstream clientFile;
	clientFile.open("../Bank project 3/clients.txt", ios::in);
	if (clientFile.is_open())
	{
		string str;
		while (getline(clientFile, str))
		{
			clientsArr.push_back(getClientStructFromArr(str));
		}
		clientFile.close();
	}
	return clientsArr;
}

bool isClientFound(stClient &clientToFind)
{
	vector<stClient> clients = getFileClients();
	for (stClient& client : clients)
	{
		if (clientToFind.userName == client.userName && clientToFind.pinCode == client.pinCode)
		{
			clientToFind = client;
			return 1;
		}
	}
	return 0;
}

string printLineOf(int length, string shape)
{
	string str;
	for (int i = 0; i < length; i++)
	{
		str += shape;
	}
	return str;
}

void printHeader(string title, string sep)
{
	int length = 50;
	int spaces = length/2 - title.length() / 2;
	cout << printLineOf(length, sep) << endl;
	cout << "|" << printLineOf(spaces - 1, " ") << title << printLineOf(spaces - 1, " ") << "|" << endl;
	cout << printLineOf(length, sep) << endl;
}

void printMainMenuChoices()
{
	printHeader("Main Menu Screen", "=");
	cout << endl;
	cout << "\t[1] Quick Withdraw." << endl;
	cout << "\t[2] Normal Withdraw." << endl;
	cout << "\t[3] Deposit." << endl;
	cout << "\t[4] Check Balance." << endl;
	cout << "\t[5] Logout." << endl;
	cout << printLineOf(50, "=") << endl;
}

int readChoice(int start, int end)
{
	int number;
	cout << "Choose what do you want to do? [" << start<< " to " << end << "]? ";
	cin >> number;
	while (number < start || number > end)
	{
		cout << "Invalid Number, ";
		cout << "Choose what do you want to do? [" << start << " to " << end << "]? ";
		cin >> number;
	}
	return number;
}

void systemPause()
{
	cout << "Press any key to go back to main menu..." << endl;
	system("pause>0");
}

void runLogin();

void printQuickWithdrawChoices()
{
	cout << left << setw(20) << "\t[1] 20";
	cout << left << setw(20) << "[2] 50" << endl;

	cout << left << setw(20) << "\t[3] 100";
	cout << left << setw(20) << "[4] 200" << endl;

	cout << left << setw(20) << "\t[5] 400";
	cout << left << setw(20) << "[6] 600" << endl;

	cout << left << setw(20) << "\t[7] 800";
	cout << left << setw(20) << "[8] 1000" << endl;
	cout << left << setw(20) << "\t[9] Exit" << endl;
}

void changeClientDeposit(int amount, string message)
{
	if (amount < 0 && stoi(inputedClient.deposit) < -amount)
	{
		cout << "There is no enough money to withdraw!" << endl;
		return;
	}
	
	char state;
	cout << "Are you sure you want to " << message << " " << (amount < 0 ? -amount : amount) << "? Y/N? ";
	cin >> state;
	if (tolower(state) == 'y')
	{
		inputedClient.deposit = to_string(stoi(inputedClient.deposit) + amount);
		cout << "your balance is now: " << inputedClient.deposit << endl;
		updateCLientFile(inputedClient);
	}

}

void confirmQuickWithdrawChoice(enQuickWithdrawChoices choice)
{
	switch (choice)
	{
	case W20:
		changeClientDeposit(-20, "withdraw");
		systemPause();
		break;
	case W50:
		changeClientDeposit(-50, "withdraw");
		systemPause();
		break;
	case W100:
		changeClientDeposit(-100, "withdraw");
		systemPause();
		break;
	case W200:
		changeClientDeposit(-200, "withdraw");
		systemPause();
		break;
	case W400:
		changeClientDeposit(-400, "withdraw");
		systemPause();
		break;
	case W600:
		changeClientDeposit(-600, "withdraw");
		systemPause();
		break;
	case W800:
		changeClientDeposit(-800, "withdraw");
		systemPause();
		break;
	case W1000:
		changeClientDeposit(-1000, "withdraw");
		systemPause();
		break;
	case Exit:
		break;
	default:
		break;
	}
}

void quickWithdraw()
{
	system("cls");
	printHeader("Quick Withdraw", "-");

	printQuickWithdrawChoices();
	cout << printLineOf(50, "-") << endl << endl;

	cout << "Your balance is: " << inputedClient.deposit << endl;
	enQuickWithdrawChoices choice = (enQuickWithdrawChoices)readChoice(1, 9);

	confirmQuickWithdrawChoice(choice);

}

void normalWithdraw()
{
	system("cls");
	printHeader("Normal Withdraw", "-");

	cout << "Your balance is: " << inputedClient.deposit << endl;
	int number;
	cout << "Enter a number to withdraw 5 and its multiplies? ";
	cin >> number;
	if (number % 5 != 0 || number == 0)
	{
		cout << "You should withdraw 5 and its multiplies, press any key to withdraw again..." << endl;
		system("pause>0");
		normalWithdraw();
	}
	else
		changeClientDeposit(-number, "withdraw");
}

void deposit()
{
	system("cls");
	printHeader("Deposit", "-");

	cout << "Your balance is: " << inputedClient.deposit << endl;
	int number;
	cout << "Enter a number to deposit? ";
	cin >> number;
	changeClientDeposit(number, "deposit");
}

void checkBalance()
{
	system("cls");
	printHeader("Check Balance", "-");
	cout << endl;
	cout << printLineOf(50, "+") << endl;
	cout << "Your balance is: " << inputedClient.deposit << endl;
	cout << printLineOf(50, "+") << endl;
}

void confirmChoices(enMainMenuChoices choice)
{
	switch (choice)
	{
	case QuickWithdraw:
		quickWithdraw();
		break;
	case NormalWithdraw:
		normalWithdraw();
		systemPause();
		break;
	case Deposit:
		deposit();
		systemPause();
		break;
	case CheckBalance:
		checkBalance();
		systemPause();
		break;
	case Logout:
		runLogin();
		break;
	default:
		break;
	}
}

void runATMapp()
{
	enMainMenuChoices choice;
	do
	{
		system("cls");
		printMainMenuChoices();
		choice = (enMainMenuChoices)readChoice(1, 5);
		confirmChoices(choice);

	} while (true);
}

void runLogin()
{
	
	system("cls");
	printHeader("Login Screen", "*");
	cout << endl;
	inputedClient = readUserAndPass();
	while (!isClientFound(inputedClient))
	{
		cout << "Username/pincode is invalid!, ";
		inputedClient = readUserAndPass();
	}

	runATMapp();

}

int main()
{
	runLogin();

	return 0;
}