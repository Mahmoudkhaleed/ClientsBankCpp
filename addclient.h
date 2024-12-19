#pragma once
#include "global.h"

namespace addclient
{
    void addLineToCleintsFile(string str)
    {
        fstream myFile;
        myFile.open("clients.txt", ios::out | ios::app);
        if (myFile.is_open())
        {
            myFile << str << endl;
            myFile.close();
        }
    }

    void fillStructWithData(global::stClient& client)
    {
        client.accNumber = global::readStr("Enter Account Number? ");
        client.pinCode = global::readStr("Enter pinCode? ");
        client.name = global::readSFullLine("Enter The Name? ");
        client.phone = global::readStr("Enter The phone? ");
        client.accBalance = global::readStr("Enter Account Balance? ");
    }

    void addNewClient()
    {
        string number;
        cout << "Enter an account number? ";
        cin >> number;
        global::stClient client;
        vector<global::stClient> arr = global::readCLientsFileToArray();
        if (global::findClient(arr, number, client))
        {
            cout << "the account with " << number << " account number is already exist\n";
        }
        else
        {
            client.accNumber = number;
            global::updateClientStruct(client);
            string str = global::convertRecordToLine(client);
            addLineToCleintsFile(str);
            cout << "Client is added successfully! ";
        }
        
    }

    void addClients()
    {
        char state;
        do
        {
            system("cls");
            global::titleFrame("Add New Client");
            addNewClient();
            cout << "Do you want to add more clients? Y/N? ";
            cin >> state;
        } while (state == 'y' || state == 'Y');
    }
}