#pragma once
#include "global.h"

namespace showlist
{
    void printClientInfoInline(global::stClient& client)
    {
        cout << "| " << left << setw(16) << client.accNumber;
        cout << "| " << left << setw(15) << client.pinCode;
        cout << "| " << left << setw(24) << client.name;
        cout << "| " << left << setw(17) << client.phone;
        cout << "| " << left << setw(16) << client.accBalance << endl;
    }

    void clientFrameToPrint()
    {
        system("cls");
        vector<global::stClient> arr = global::readCLientsFileToArray();
        cout << "\t\t\t\t\tClient List (" << arr.size() << ") Client/s" << endl;
        cout << global::makeLineOf(95) << endl << endl;
        cout << "| " << left << setw(3) << "I";
        cout << "| " << left << setw(16) << "Account Number";
        cout << "| " << left << setw(15) << "Pin Code";
        cout << "| " << left << setw(24) << "Client Name";
        cout << "| " << left << setw(17) << "Phone";
        cout << "| " << left << setw(16) << "Balance" << endl;
        cout << global::makeLineOf(95) << endl << endl;
        for (int i = 0; i < arr.size(); i++)
        {
            cout << "| " << left << setw(3) << i + 1;
            printClientInfoInline(arr[i]);
        }
        cout << global::makeLineOf(95) << endl;
    }
}