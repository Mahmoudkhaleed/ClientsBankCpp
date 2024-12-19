#pragma once
#include "global.h"

namespace deleteclient
{
    string getAccountNumber()
    {
        string num;
        cout << "Enter an account number to Delete? ";
        cin >> num;
        return num;
    }

    void proceedToDelete(string& num, vector<global::stClient>& newArr)
    {
        global::stClient client;
        vector<global::stClient> oldArr = global::readCLientsFileToArray();
        char sure;
        if (global::findClient(oldArr, num, client))
        {
            for (global::stClient c : oldArr)
            {
                if (c.accNumber != num)
                    newArr.push_back(c);
            }
            global::printClientCard(client);
            cout << "are you sure you want to delete? Y/N ";
            cin >> sure;
            if (tolower(sure) == 'y')
            {
                global::updateClientsFile(newArr);
                cout << "the account number (" << num << ") is deleted successfully!" << endl;
            }
        }
        else
        {
            cout << "this account data with (" << num << ") is not available!\n";
        }
    }

    void deleteClient()
    {
        char state;
        do
        {
            system("cls");
            global::titleFrame("Delete Screen for clients");
            string num = getAccountNumber();
            vector<global::stClient> newArr;

            proceedToDelete(num, newArr);

            cout << "Do you want to delete another account? Y/N\n";
            cin >> state;
        } while (tolower(state) == 'y');
    }
}