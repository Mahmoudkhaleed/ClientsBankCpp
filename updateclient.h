#pragma once
#include "global.h"

namespace update
{
    string readAnAccountNumber()
    {
        string number;
        cout << "Please enter an account number to update? ";
        cin >> number;
        return number;
    }

    void confirmUpdate(vector<global::stClient>& arr, string number)
    {
        char state;
        cout << "Are you sure you want to update this client? Y/N ";
        cin >> state;
        if (tolower(state) == 'y')
        {
            for (global::stClient& client : arr)
            {
                if (client.accNumber == number)
                {
                    global::updateClientStruct(client);
                    break;
                }
            }
            global::updateClientsFile(arr);

            cout << "Client was updated successfully!\n";
        }
    }

    void updateClientData()
    {
        string accNum = readAnAccountNumber();
        global::stClient client;
        vector<global::stClient> arr = global::readCLientsFileToArray();
        if (findClient(arr, accNum, client))
        {
            global::printClientCard(client);
            confirmUpdate(arr, accNum);
        }
        else
        {
            cout << "client with " << accNum << " account number is not found" << endl;
        }
    }

    void updateClient()
    {
        char state;

        do
        {
            system("cls");
            updateClientData();
            cout << "do you want to update another client? Y/N ";
            cin >> state;
        } while (tolower(state) == 'y');
    }
}