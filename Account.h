#pragma once
#include <iostream>
#include <fstream>
#include "Bank.h"
#include "User.h"
#include "Transection.h"
#include <string>
#include <vector>
#include "validations.h"
using namespace std;

class Account
{
private:
    int accId;
    int accUserId;
    unsigned long long accNumber;
    string accHolder = "";
    float balance;
    string UPI = "";
    int accPin;

public:
    // Making class 'Bank' as friend; so that bank can access all the data of accounts.
    friend class Bank;
    string accType;
    string IFSCcode = "AMT0474005";
    // Vector of transection objects to store transection entries
    vector<Transection> transections;

    Account()
    {
        accId = 0, accUserId = 0, accNumber = 0;
        balance = 0, accPin = 0;
    }
    Account(int _userId, int setAccId, unsigned long long _accNo, long _phoneNo)
    {
        accId = setAccId;
        accNumber = _accNo;
        accUserId = _userId;
        int option;
        do
        {
            system("cls");
            cout << "Select: [1] Savings \t [2] Current" << endl;
            option = input_int();
            if (option == 1)
            {
                accType = "Savings";
            }
            else
            {
                accType = "Current";
            }
        } while (option != 1 && option != 2);
        system("cls");
        cout << endl
             << "Enter account Holders name" << endl;
        accHolder = input_strictString();
        system("cls");
        cout << endl
             << "Set transection pin (Applicable to UPI & direct account transfers)" << endl;
        accPin = input_int();
        system("cls");
        cout << endl
             << "Enter Opening balance: " << endl;
        do
        {
            balance = input_float();
        } while (balance <= 0 || balance > 9999);
        UPI = to_string(_userId) + to_string(_phoneNo % 1000) + to_string(_accNo % 1000) + "@AmiBnk";
        system("cls");
        cout << "Success! Account created!" << endl;
        cout << endl
             << "Account number: " << accNumber << endl;
        cout << endl
             << "Account holder's name: " << accHolder << endl;
        cout << endl
             << "UPI id: " << UPI << endl;
        pauseConsole();
    }

    // To update the account
    void accUpdateName(string _accHolder) { accHolder = _accHolder; }
    // To get account Id
    const int getAccId() { return accId; }
    // To get the Account Number
    void updateAccId(int newAccId) { accId = newAccId; }
    // To get the Account Number
    const unsigned long long getAccNumber() { return accNumber; }
    // To get the acount holder's name
    string getAccHolder() { return accHolder; }
    // To get the transection pin.
    const int getPin() { return accPin; }
    // to set the balance
    void setBalance(const float _balance) { balance = _balance; }
    // To get the balance
    const float getBalance() { return balance; }
    // To ge UPI
    string getUpi() { return UPI; }
    // To close the account

    // to list all transections for *this account
    void listTransections()
    {
        system("cls");
        for (auto trans : transections)
        {
            cout << endl
                 << endl;
            cout << "Transection ID: " << trans.transId << endl;
            cout << "Transection type: " << trans.type << endl;
            cout << "amount: Rs." << trans.amount << endl;
            cout << "from: " << trans.from << endl;
            cout << "to: " << trans.to_acc << endl;
            cout << "mode : " << trans.mode << endl;
            cout << "Transection Time: " << trans.transTime << endl;
        }
        pauseConsole();
    }

    // ~Account()
    // {
    //     cout << "Account closed | Closing balanace: " << balance << endl;
    // }

    void save_csv_data(ofstream &accounts_csv)
    {
        // Save the created object in account_csv file.
        accounts_csv << accId << "," << accUserId << "," << static_cast<long long>(accNumber) << "," << accHolder << "," << balance << "," << UPI << "," << accPin << "," << accType << endl;
    }

    bool load_csv_data(string lineBuffer)
    {
        istringstream iss(lineBuffer);
        string fieldBuffer;
        getline(iss, fieldBuffer, ',');
        accId = stoi(fieldBuffer);
        getline(iss, fieldBuffer, ',');
        accUserId = stoi(fieldBuffer);
        getline(iss, fieldBuffer, ',');
        accNumber = (stoull(fieldBuffer));
        getline(iss, fieldBuffer, ',');
        accHolder = (fieldBuffer);
        getline(iss, fieldBuffer, ',');
        balance = (stof(fieldBuffer));
        getline(iss, fieldBuffer, ',');
        UPI = (fieldBuffer);
        getline(iss, fieldBuffer, ',');
        accPin = (stoi(fieldBuffer));
        getline(iss, fieldBuffer, ',');
        accType = (fieldBuffer);

        return true;
    }
};