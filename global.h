#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

namespace global
{
    struct stClient
    {
        string accNumber;
        string pinCode;
        string name;
        string phone;
        string accBalance;
    };

    string readSFullLine(string mess)
    {
        string str;
        cout << mess;
        cin.ignore(1, '\n');
        getline(cin, str);
        return str;
    }

    string readStr(string mess)
    {
        string str;
        cout << mess;
        cin >> str;
        return str;
    }

    vector<string> convertStrLineToArrOfStrs(string line, string delim = "#//#")
    {
        vector<string> arr;
        string str;
        int pos;

        while ((pos = line.find(delim)) != string::npos)
        {
            str = line.substr(0, pos);
            arr.push_back(str);
            line.erase(0, pos + delim.length());
        }

        if (!empty(line))
        {
            arr.push_back(line);
        }
        return arr;
    }

    stClient fillClientStructWithDataFormLine(string str)
    {
        vector<string> arr = convertStrLineToArrOfStrs(str);
        stClient client;
        client.accNumber = arr[0];
        client.pinCode = arr[1];
        client.name = arr[2];
        client.phone = arr[3];
        client.accBalance = arr[4];
        return client;
    }

    void updateClientStruct(global::stClient& client)
    {
        //client.accNumber = readStr("Enter Account Number? ");
        client.pinCode = global::readStr("Enter pinCode? ");
        client.name = global::readSFullLine("Enter The Name? ");
        client.phone = global::readStr("Enter The phone? ");
        client.accBalance = global::readStr("Enter Account Balance? ");
    }

    vector<stClient> readCLientsFileToArray()
    {
        vector<stClient> clients;
        fstream clientsFile;
        clientsFile.open("clients.txt", ios::in);
        if (clientsFile.is_open())
        {
            string str;
            while (getline(clientsFile, str))
            {
                clients.push_back(fillClientStructWithDataFormLine(str));
            }
            clientsFile.close();
        }
        return clients;
    }

    string convertRecordToLine(stClient& client, string sep = "#//#")
    {
        string str;
        str += client.accNumber + sep;
        str += client.pinCode + sep;
        str += client.name + sep;
        str += client.phone + sep;
        str += client.accBalance;
        return str;
    }

    void updateClientsFile(vector<stClient>& arr)
    {
        fstream clientsFile;
        clientsFile.open("clients.txt", ios::out);
        if (clientsFile.is_open())
        {
            for (stClient& client : arr)
            {
                clientsFile << convertRecordToLine(client) << endl;
            }
            clientsFile.close();
        }
    }

    string makeLineOf(int number, char symbol = '_')
    {
        string str;
        for (int i = 0; i < number; i++)
            str += symbol;
        return str;
    }

    bool findClient(vector<stClient>& arr, string number, stClient& client)
    {
        for (stClient& c : arr)
        {
            if (c.accNumber == number)
            {
                client = c;
                return 1;
            }
        }
        return 0;
    }

    void printClientCard(stClient& client)
    {
        cout << "\nThe following are the client details\n";
        cout << "-------------------\n";
        cout << "Account number  : " << client.accNumber << endl;
        cout << "Pin Code        : " << client.pinCode << endl;
        cout << "Account Name    : " << client.name << endl;
        cout << "Account Phone   : " << client.phone << endl;
        cout << "Account Balance : " << client.accBalance << endl;
        cout << "-------------------\n";
    }

    void titleFrame(string str, char theme = '-')
    {
        cout << makeLineOf(40, theme) << endl;
        cout << "|  " << makeLineOf(17 - str.length() / 2, ' ') << str << " " << makeLineOf(15 - str.length() / 2, ' ') << "  |" << endl;
        cout << makeLineOf(40, theme) << endl << endl;
    }

}